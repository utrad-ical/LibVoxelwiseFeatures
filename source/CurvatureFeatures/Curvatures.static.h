


//#ifdef __cplusplus
//extern "C" {
//#endif // __cplusplus //

// static void	calc_second_derivatives(void* array,int unit,VOL_INTSIZE4D* matrixSize,VOL_INTVECTOR3D* position,VOL_VECTOR3D* eigenvectors,float* eigenvalues );
// static int	setup_gaussian_kernels(float sigma);
// static void	adapt_gaussian_kernels(VOL_INTSIZE4D* matrixSizeOftargetVolumeData);
// static void	delete_gaussian_kernels();

// static float local_gradient(void* array, int unit, VOL_INTSIZE4D* matrixSize, VOL_INTVECTOR3D* position, char angle);
// static void calc_second_derivatives_plus(
//	void* array, int unit, VOL_INTSIZE4D* matrixSize, VOL_INTVECTOR3D* position, VOL_VECTOR3D* eigenvectors, float* eigenvalues, float* curvatures);

//#ifdef __cplusplus
//}
//#endif // __cplusplus //


static VOL_KERNEL*		d2x=NULL;
static VOL_KERNEL*		d2y=NULL;
static VOL_KERNEL*		d2z=NULL;
static VOL_KERNEL*		dxdy=NULL;
static VOL_KERNEL*		dydz=NULL;
static VOL_KERNEL*		dzdx=NULL;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


template <class VARTYPE>
float
calc_local_convolution(VARTYPE* data,VOL_INTSIZE4D* matrixSize,VOL_INTVECTOR3D* position,VOL_KERNEL* kernel)
{
	int			width = matrixSize->width;
	int			height = matrixSize->height;
	VARTYPE*	dataPtr = data;
	int*		rpPtr = kernel->locationArray->rasterPosition;
	int			nPnts = kernel->locationArray->nElements;
	float*		wPtr = kernel->weight;
	
	float		value = 0.0f;

	dataPtr = data + position->z*width*height + position->y*width + position->x;

	for(int pt=0;pt<nPnts;pt++)
	{
		//fprintf(stderr,"(%fx%f),",(float)(*(dataPtr + *rpPtr)),*wPtr);
		value += (float)(*(dataPtr + *rpPtr++))*(*wPtr++);
	}
	//fprintf(stderr,"\n");
	return value;
}

template float	calc_local_convolution(unsigned char* data,VOL_INTSIZE4D* matrixSize,VOL_INTVECTOR3D* position,VOL_KERNEL* kernel);
template float	calc_local_convolution(char* data,VOL_INTSIZE4D* matrixSize,VOL_INTVECTOR3D* position,VOL_KERNEL* kernel);
template float	calc_local_convolution(unsigned short* data,VOL_INTSIZE4D* matrixSize,VOL_INTVECTOR3D* position,VOL_KERNEL* kernel);
template float	calc_local_convolution(short* data,VOL_INTSIZE4D* matrixSize,VOL_INTVECTOR3D* position,VOL_KERNEL* kernel);
template float	calc_local_convolution(unsigned int* data,VOL_INTSIZE4D* matrixSize,VOL_INTVECTOR3D* position,VOL_KERNEL* kernel);
template float	calc_local_convolution(int* data,VOL_INTSIZE4D* matrixSize,VOL_INTVECTOR3D* position,VOL_KERNEL* kernel);
template float	calc_local_convolution(float* data,VOL_INTSIZE4D* matrixSize,VOL_INTVECTOR3D* position,VOL_KERNEL* kernel);
template float	calc_local_convolution(double* data,VOL_INTSIZE4D* matrixSize,VOL_INTVECTOR3D* position,VOL_KERNEL* kernel);


static void		draw_gauss_volume(float*** array3D,int radius,float sigma);
static float	local_convolution(void* array,int unit,VOL_INTSIZE4D* matrixSize,VOL_INTVECTOR3D* position,VOL_KERNEL* kernel);



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


template <class VARTYPE>
float calc_local_gradient(VARTYPE* data, VOL_INTSIZE4D* matrixSize, VOL_INTVECTOR3D* position, char angle)
{
	int	width = matrixSize->width;
	int	height = matrixSize->height;
	int xye = height*width;
	int raster = position->z*xye+position->y*width+position->x;

	switch( angle ) {
		case 'x':	return (float)(data[raster+1]-data[raster-1]);
		case 'y':	return (float)(data[raster+width]-data[raster-width]);
		case 'z':	return (float)(data[raster+xye]-data[raster-xye]);
		default:	return 0.0f;
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



static float sqrarg;
#define SQR(a) ((sqrarg=(a)) == 0.0 ? 0.0 : sqrarg*sqrarg)

#define SIGN(a,b) ((b) >= 0.0 ? fabs(a) : -fabs(a))


static float
pythag(float a, float b)
{
	float absa,absb;
	absa=fabs(a);
	absb=fabs(b);
	if (absa > absb) return (float)(absa*sqrt(1.0+SQR(absb/absa)));
	else return (float)(absb == 0.0 ? 0.0 : absb*sqrt(1.0+SQR(absa/absb)));
}



static void
tqli(float d[], float e[], int n, float **z)
{
	int m,l,iter,i,k;
	float s,r,p,g,f,dd,c,b;

	for (i=2;i<=n;i++) e[i-1]=e[i];
	e[n]=0.0;
	for (l=1;l<=n;l++) {
		iter=0;
		do {
			for (m=l;m<=n-1;m++) {
				dd=fabs(d[m])+fabs(d[m+1]);
				if ((float)(fabs(e[m])+dd) == dd) break;
			}
			if (m != l) {
				if (iter++ == 30)
				{
					/*
					nrerror("Too many iterations in tqli");
					fprintf(stderr,"NR-ERROR: Too many iterations in tqli");
					*/
					z[1][1]=z[2][2]=z[3][3]=1.0;
					z[1][2]=z[2][1]=z[2][3]=z[3][2]=z[3][1]=z[1][3]=0.0;
					d[1]=d[2]=d[3]=0.00000000000001;
					e[1]=e[2]=e[3]=0.00000000000001;
					return;
				}
				g=(d[l+1]-d[l])/(2.0f*e[l]);
				r=pythag(g,1.0);
				g=d[m]-d[l]+e[l]/(g+SIGN(r,g));
				s=c=1.0;
				p=0.0;
				for (i=m-1;i>=l;i--) {
					f=s*e[i];
					b=c*e[i];
					e[i+1]=(r=pythag(f,g));
					if (r == 0.0) {
						d[i+1] -= p;
						e[m]=0.0;
						break;
					}
					s=f/r;
					c=g/r;
					g=d[i+1]-p;
					r=(d[i]-g)*s+2.0f*c*b;
					d[i+1]=g+(p=s*r);
					g=c*r-b;
					for (k=1;k<=n;k++) {
						f=z[k][i+1];
						z[k][i+1]=s*z[k][i]+c*f;
						z[k][i]=c*z[k][i]-s*f;
					}
				}
				if (r == 0.0 && i >= l) continue;
				d[l] -= p;
				e[l]=g;
				e[m]=0.0;
			}
		} while (m != l);
	}
}


static void
tred2(float **a, int n, float d[], float e[])
{
	int l,k,j,i;
	float scale,hh,h,g,f;

	for (i=n;i>=2;i--) {
		l=i-1;
		h=scale=0.0;
		if (l > 1) {
			for (k=1;k<=l;k++)
				scale += fabs(a[i][k]);
			if (scale == 0.0)
				e[i]=a[i][l];
			else {
				for (k=1;k<=l;k++) {
					a[i][k] /= scale;
					h += a[i][k]*a[i][k];
				}
				f=a[i][l];
				g=(f >= 0.0 ? -sqrt(h) : sqrt(h));
				e[i]=scale*g;
				h -= f*g;
				a[i][l]=f-g;
				f=0.0;
				for (j=1;j<=l;j++) {
					a[j][i]=a[i][j]/h;
					g=0.0;
					for (k=1;k<=j;k++)
						g += a[j][k]*a[i][k];
					for (k=j+1;k<=l;k++)
						g += a[k][j]*a[i][k];
					e[j]=g/h;
					f += e[j]*a[i][j];
				}
				hh=f/(h+h);
				for (j=1;j<=l;j++) {
					f=a[i][j];
					e[j]=g=e[j]-hh*f;
					for (k=1;k<=j;k++)
						a[j][k] -= (f*e[k]+g*a[i][k]);
				}
			}
		} else
			e[i]=a[i][l];
		d[i]=h;
	}
	d[1]=0.0;
	e[1]=0.0;
	/* Contents of this loop can be omitted if eigenvectors not
			wanted except for statement d[i]=a[i][i]; */
	for (i=1;i<=n;i++) {
		l=i-1;
		if (d[i]) {
			for (j=1;j<=l;j++) {
				g=0.0;
				for (k=1;k<=l;k++)
					g += a[i][k]*a[k][j];
				for (k=1;k<=l;k++)
					a[k][j] -= g*a[k][i];
			}
		}
		d[i]=a[i][i];
		a[i][i]=1.0;
		for (j=1;j<=l;j++) a[j][i]=a[i][j]=0.0;
	}
}


#define SWAP(a,b) temp=(a);(a)=(b);(b)=temp;
#define M 7
#define NSTACK 50

static void sort2(unsigned int n, float arr[], float brr[])
{
	unsigned int	i,ir=n,j,k,l=1;
	int				istack[NSTACK+1], jstack=0;
	float a,b,temp;

	for (;;) {
		if (ir-l < M) {
			for (j=l+1;j<=ir;j++) {
				a=arr[j];
				b=brr[j];
				for (i=j-1;i>=1;i--) {
					if (arr[i] <= a) break;
					arr[i+1]=arr[i];
					brr[i+1]=brr[i];
				}
				arr[i+1]=a;
				brr[i+1]=b;
			}
			if (!jstack) {
				return;
			}
			ir=istack[jstack];
			l=istack[jstack-1];
			jstack -= 2;
		} else {
			k=(l+ir) >> 1;
			SWAP(arr[k],arr[l+1])
			SWAP(brr[k],brr[l+1])
			if (arr[l+1] > arr[ir]) {
				SWAP(arr[l+1],arr[ir])
				SWAP(brr[l+1],brr[ir])
			}
			if (arr[l] > arr[ir]) {
				SWAP(arr[l],arr[ir])
				SWAP(brr[l],brr[ir])
			}
			if (arr[l+1] > arr[l]) {
				SWAP(arr[l+1],arr[l])
				SWAP(brr[l+1],brr[l])
			}
			i=l+1;
			j=ir;
			a=arr[l];
			b=brr[l];
			for (;;) {
				do i++; while (arr[i] < a);
				do j--; while (arr[j] > a);
				if (j < i) break;
				SWAP(arr[i],arr[j])
				SWAP(brr[i],brr[j])
			}
			arr[l]=arr[j];
			arr[j]=a;
			brr[l]=brr[j];
			brr[j]=b;
			jstack += 2;
			if (jstack > NSTACK) return;
			if (ir-i+1 >= j-l) {
				istack[jstack]=ir;
				istack[jstack-1]=i;
				ir=j-1;
			} else {
				istack[jstack]=j-1;
				istack[jstack-1]=l;
				l=i;
			}
		}
	}
}
#undef M
#undef SWAP
#undef NSTACK


