/*     CalculiX - A 3-dimensional finite element program                 */
/*              Copyright (C) 1998-2023 Guido Dhondt                          */

/*     This program is free software; you can redistribute it and/or     */
/*     modify it under the terms of the GNU General Public License as    */
/*     published by the Free Software Foundation(version 2);    */
/*                                                                       */

/*     This program is distributed in the hope that it will be useful,   */
/*     but WITHOUT ANY WARRANTY; without even the implied warranty of    */
/*     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the      */
/*     GNU General Public License for more details.                      */

/*     You should have received a copy of the GNU General Public License */
/*     along with this program; if not, write to the Free Software       */
/*     Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.         */

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "CalculiX.h"

void csvgeneralvector(double *v, ITG *iset, ITG *ntrans, char *filabl,
					  ITG *nkcoords, ITG *inum, ITG *inotr, double *trab,
					  double *co, ITG *istartset, ITG *iendset, ITG *ialset,
					  ITG *mi, ITG *ngraph, char *output, char *header,
					  char *set, char *variable, char *time_step)
{

	FILE *f1;
	char csv_filename[64];

	sprintf(csv_filename, "FILE_%s_%s_%s.csv", variable, set, time_step);
	f1 = fopen(csv_filename, "w");
	if (f1 == NULL)
	{
		fprintf(stderr, "Couldn't open %s\n", csv_filename);
		exit(1);
	}

	fprintf(f1, header);

	ITG i, j, k, l, m, nksegment;

	int iw;

	float fl;

	double a[9];

	if (*iset == 0)
	{
		if ((*ntrans == 0) || (strcmp1(&filabl[5], "G") == 0))
		{
			for (i = 0; i < *nkcoords; i++)
			{
				if (inum[i] <= 0)
					continue;
				if (mi[1] == 4)
				{
					fprintf(f1, "%" ITGFORMAT ",%12.5E,%12.5E,%12.5E,%12.5E\n", i + 1,
							(float)v[(mi[1] + 1) * i + 1], (float)v[(mi[1] + 1) * i + 2],
							(float)v[(mi[1] + 1) * i + 3], (float)v[(mi[1] + 1) * i + 4]);
				}
				else if (mi[1] == 5)
				{
					fprintf(f1, "%" ITGFORMAT ",%12.5E,%12.5E,%12.5E,%12.5E,%12.5E\n", i + 1,
							(float)v[(mi[1] + 1) * i + 1], (float)v[(mi[1] + 1) * i + 2],
							(float)v[(mi[1] + 1) * i + 3], (float)v[(mi[1] + 1) * i + 4],
							(float)v[(mi[1] + 1) * i + 5]);
				}
				else if (mi[1] == 6)
				{
					fprintf(f1, "%" ITGFORMAT ",%12.5E,%12.5E,%12.5E,%12.5E,%12.5E,%12.5E\n", i + 1,
							(float)v[(mi[1] + 1) * i + 1], (float)v[(mi[1] + 1) * i + 2],
							(float)v[(mi[1] + 1) * i + 3], (float)v[(mi[1] + 1) * i + 4],
							(float)v[(mi[1] + 1) * i + 5], (float)v[(mi[1] + 1) * i + 6]);
				}
			}
		}
		else
		{
			for (i = 0; i < *nkcoords; i++)
			{
				if (inum[i] <= 0)
					continue;
				if (inotr[2 * i] == 0)
				{

					if (mi[1] == 4)
					{
						fprintf(f1, "%" ITGFORMAT ",%12.5E,%12.5E,%12.5E,%12.5E\n", i + 1,
								(float)v[(mi[1] + 1) * i + 1], (float)v[(mi[1] + 1) * i + 2],
								(float)v[(mi[1] + 1) * i + 3], (float)v[(mi[1] + 1) * i + 4]);
					}
					else if (mi[1] == 5)
					{
						fprintf(f1, "%" ITGFORMAT ",%12.5E,%12.5E,%12.5E,%12.5E,%12.5E\n", i + 1,
								(float)v[(mi[1] + 1) * i + 1], (float)v[(mi[1] + 1) * i + 2],
								(float)v[(mi[1] + 1) * i + 3], (float)v[(mi[1] + 1) * i + 4],
								(float)v[(mi[1] + 1) * i + 5]);
					}
					else if (mi[1] == 6)
					{
						fprintf(f1, "%" ITGFORMAT ",%12.5E,%12.5E,%12.5E,%12.5E,%12.5E,%12.5E\n", i + 1,
								(float)v[(mi[1] + 1) * i + 1], (float)v[(mi[1] + 1) * i + 2],
								(float)v[(mi[1] + 1) * i + 3], (float)v[(mi[1] + 1) * i + 4],
								(float)v[(mi[1] + 1) * i + 5], (float)v[(mi[1] + 1) * i + 6]);
					}
				}
				else
				{
					printf(" *WARNING in csvgeneralvector:\n");
					printf("          no output in local coordinates allowed\n");
					printf("          for generalized vectors\n");
					printf("          output request ist not performed;\n");
				}
			}
		}
	}
	else
	{
		nksegment = (*nkcoords) / (*ngraph);
		for (k = istartset[*iset - 1] - 1; k < iendset[*iset - 1]; k++)
		{
			if (ialset[k] > 0)
			{
				for (l = 0; l < *ngraph; l++)
				{
					i = ialset[k] + l * nksegment - 1;
					if (inum[i] <= 0)
						continue;
					if ((*ntrans == 0) || (strcmp1(&filabl[5], "G") == 0) || (inotr[2 * i] == 0))
					{
						if (mi[1] == 4)
						{
							fprintf(f1, "%" ITGFORMAT ",%12.5E,%12.5E,%12.5E,%12.5E\n", i + 1,
									(float)v[(mi[1] + 1) * i + 1], (float)v[(mi[1] + 1) * i + 2],
									(float)v[(mi[1] + 1) * i + 3], (float)v[(mi[1] + 1) * i + 4]);
						}
						else if (mi[1] == 5)
						{
							fprintf(f1, "%" ITGFORMAT ",%12.5E,%12.5E,%12.5E,%12.5E,%12.5E\n", i + 1,
									(float)v[(mi[1] + 1) * i + 1], (float)v[(mi[1] + 1) * i + 2],
									(float)v[(mi[1] + 1) * i + 3], (float)v[(mi[1] + 1) * i + 4],
									(float)v[(mi[1] + 1) * i + 5]);
						}
						else if (mi[1] == 6)
						{
							fprintf(f1, "%" ITGFORMAT ",%12.5E,%12.5E,%12.5E,%12.5E,%12.5E,%12.5E\n", i + 1,
									(float)v[(mi[1] + 1) * i + 1], (float)v[(mi[1] + 1) * i + 2],
									(float)v[(mi[1] + 1) * i + 3], (float)v[(mi[1] + 1) * i + 4],
									(float)v[(mi[1] + 1) * i + 5], (float)v[(mi[1] + 1) * i + 6]);
						}
					}
					else
					{
						printf(" *WARNING in csvgeneralvector:\n");
						printf("          no output in local coordinates allowed\n");
						printf("          for generalized vectors\n");
						printf("          output request ist not performed;\n");
					}
				}
			}
			else
			{
				l = ialset[k - 2];
				do
				{
					l -= ialset[k];
					if (l >= ialset[k - 1])
						break;
					for (m = 0; m < *ngraph; m++)
					{
						i = l + m * nksegment - 1;
						if (inum[i] <= 0)
							continue;
						if ((*ntrans == 0) || (strcmp1(&filabl[5], "G") == 0) || (inotr[2 * i] == 0))
						{
							if (mi[1] == 4)
							{
								fprintf(f1, "%" ITGFORMAT ",%12.5E,%12.5E,%12.5E,%12.5E\n", i + 1,
										(float)v[(mi[1] + 1) * i + 1], (float)v[(mi[1] + 1) * i + 2],
										(float)v[(mi[1] + 1) * i + 3], (float)v[(mi[1] + 1) * i + 4]);
							}
							else if (mi[1] == 5)
							{
								fprintf(f1, "%" ITGFORMAT ",%12.5E,%12.5E,%12.5E,%12.5E,%12.5E\n", i + 1,
										(float)v[(mi[1] + 1) * i + 1], (float)v[(mi[1] + 1) * i + 2],
										(float)v[(mi[1] + 1) * i + 3], (float)v[(mi[1] + 1) * i + 4],
										(float)v[(mi[1] + 1) * i + 5]);
							}
							else if (mi[1] == 6)
							{
								fprintf(f1, "%" ITGFORMAT ",%12.5E,%12.5E,%12.5E,%12.5E,%12.5E,%12.5E\n", i + 1,
										(float)v[(mi[1] + 1) * i + 1], (float)v[(mi[1] + 1) * i + 2],
										(float)v[(mi[1] + 1) * i + 3], (float)v[(mi[1] + 1) * i + 4],
										(float)v[(mi[1] + 1) * i + 5], (float)v[(mi[1] + 1) * i + 6]);
							}
						}
						else
						{
							printf(" *WARNING in csvgeneralvector:\n");
							printf("          no output in local coordinates allowed\n");
							printf("          for generalized vectors\n");
							printf("          output request ist not performed;\n");
						}
					}
				} while (1);
			}
		}
	}

	if (strcmp1(output, "asc") == 0)
		fprintf(f1, "\n");

	return;
}
