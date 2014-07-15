#include<stdio.h>
#include<math.h>

#include "VOL.h"

//----------------------------------------------------------------------------------------------------------------------
// Calclation of Eigen value and Eigen vector for real symmetrical matrix (using Jacobi method)
// a : Matrix A (VOL_MATRIX structure)
// d : Output of eigen value  (VOL_VECTOR structure)
// v : Output of eigen vector (VOL_MATRIX structure)
// nrot : Number of Jacobi rotation
//----------------------------------------------------------------------------------------------------------------------
void jacobi(VOL_MATRIX *a, VOL_VECTOR *d, VOL_MATRIX *v, int *nrot)
{
	int j, iq, ip, i;
	int n = a->n;
	float tresh, theta, tau, t, sm, s, h, g, c;

	VolVector *b = VOL_NewVector(a->n);
	VolVector *z = VOL_NewVector(a->n);

	for (ip=0; ip<n; ip++)
	{
		for (iq=0; iq<n; iq++) v->data[ip][iq]=0.0f;
		v->data[ip][ip]=1.0f;
	}

	for (ip=0; ip<n; ip++)
	{
		b->data[ip] = d->data[ip] = a->data[ip][ip];
		z->data[ip] = 0.0f;
	}

	*nrot=0;
	for(i=1; i<50; i++)
	{
		sm=0.0f;
		for (ip=0; ip<n-1; ip++)
		{
			for (iq=ip+1; iq<n; iq++){  sm += fabs(a->data[ip][iq]);  }
		}
		//cout << sm << endl;

		if (sm == 0.0f)
		{
			VOL_DeleteVector(b);
			VOL_DeleteVector(z);
			return;
		}

		tresh = (i < 4) ? 0.2f * sm / (n * n) : 0.0f;

		for (ip=0; ip<n-1; ip++)
		{
			for (iq=ip+1; iq<n; iq++)
			{
				g = 100.0f * fabs(a->data[ip][iq]);
				if (i > 4 && (float)(fabs(d->data[ip])+g) == (float)fabs(d->data[ip])
					&& (float)(fabs(d->data[iq])+g) == (float)fabs(d->data[iq]))
				{
					a->data[ip][iq] = 0.0f;
				}
				else if (fabs(a->data[ip][iq]) > tresh)
				{
					h = d->data[iq] - d->data[ip];
					if ((float)(fabs(h)+g) == (float)fabs(h))
					{
						t=(a->data[ip][iq])/h;
					}
					else
					{
						theta = 0.5f * h/(a->data[ip][iq]);
						t = 1.0f/(fabs(theta)+sqrt(1.0f+theta*theta));
						if (theta < 0.0f) t = -t;
					}
					c=1.0f/sqrt(1.0f + t * t);
					s = t * c;
					tau = s / (1.0f + c);
					h = t * a->data[ip][iq];
					z->data[ip] -= h;
					z->data[iq] += h;
					d->data[ip] -= h;
					d->data[iq] += h;
					a->data[ip][iq]=0.0f;

					for (j=0; j<ip; j++)
					{
						//ROTATE(a,j,ip,j,iq)
						g=a->data[j][ip];
						h=a->data[j][iq];
						a->data[j][ip] = g - s * (h + g*tau);
						a->data[j][iq] = h + s * (g-h*tau);
					}
					for (j=ip+1; j<iq; j++)
					{
						//dataROTATE(a,ip,j,j,iq)
						g=a->data[ip][j];
						h=a->data[j][iq];
						a->data[ip][j] = g - s * (h + g*tau);
						a->data[j][iq] = h + s * (g-h*tau);
					}
					for (j=iq+1; j<n; j++)
					{
						//ROTATE(a,ip,j,iq,j)
						g=a->data[ip][j];
						h=a->data[iq][j];
						a->data[ip][j] = g - s * (h + g*tau);
						a->data[iq][j] = h + s * (g-h*tau);
					}
					for (j=0; j<n; j++)
					{
						//ROTATE(v,j,ip,j,iq)
						g=v->data[j][ip];
						h=v->data[j][iq];
						v->data[j][ip] = g - s * (h + g*tau);
						v->data[j][iq] = h + s * (g-h*tau);
					}
					//cout << *nrot << endl; 
					++(*nrot);
				}
			}
		}
		for (ip=0; ip<n; ip++)
		{
			b->data[ip] += z->data[ip];
			d->data[ip] = b->data[ip];
			z->data[ip] = 0.0f;
		}

	}
	fprintf(stderr, "Too many iterations in routine jacobi\n");
}
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Sort Eigen value and Eigen vector by ascending order
// d : Input/Output of eigen value  (VOL_VECTOR structure)
// v : Input/Output of eigen vector (VOL_MATRIX structure)
//----------------------------------------------------------------------------------------------------------------------
void eigsrt(VOL_VECTOR *d, VOL_MATRIX *v)
{
	int k,j,i;
	float p;

	int n = v->n;

	for (i=0; i<n; i++)
	{
		p = d->data[k=i];
		for(j=i+1;j<n;j++)
		{
			if (d->data[j] <= p) p=d->data[k=j];
		}
		if(k != i)
		{
			d->data[k] = d->data[i];
			d->data[i] = p;
			for (j=0; j<n; j++)
			{
				p = v->data[j][i];
				v->data[j][i] = v->data[j][k];
				v->data[j][k] = p;
			}
		}
	}
	return;
}
//----------------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------
// Sort absolute of Eigen value and Eigen vector by ascending order
// d : Input/Output of eigen value  (VOL_VECTOR structure)
// v : Input/Output of eigen vector (VOL_MATRIX structure)
//----------------------------------------------------------------------------------------------------------------------
void eigsrtabs(VOL_VECTOR *d, VOL_MATRIX *v)
{
	int k,j,i;
	float p, tmp;

	int n = v->n;

	VOL_VECTOR* AbsValue = VOL_NewVector(n);

	for(i=0; i<n; i++) AbsValue->data[i] = fabs(d->data[i]);
	
	for (i=0; i<n; i++)
	{
		p = AbsValue->data[k=i];
		tmp = d->data[i];
		for(j=i+1;j<n;j++)
		{
			if (AbsValue->data[j] >= p)
			{
				p=AbsValue->data[k=j];
				tmp = d->data[j];
			}
		}
		if(k != i)
		{
			AbsValue->data[k] = AbsValue->data[i];
			AbsValue->data[i] = p;

			d->data[k] = d->data[i];
			d->data[i] = tmp;
			for (j=0; j<n; j++)
			{
				p = v->data[j][i];
				v->data[j][i] = v->data[j][k];
				v->data[j][k] = p;
			}
		}
	}

	VOL_DeleteVector(AbsValue);

	return;
}
//----------------------------------------------------------------------------------------------------------------------