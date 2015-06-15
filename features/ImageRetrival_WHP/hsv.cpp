#include "hsv.h"
#include <iostream>
#include <fstream>
using namespace std;
//°Ñ½üËÆºÚ°×ÏñËØµã¹éÈëºÚ°×ÏñËØµã
void ZImage::HSVChange()
{
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (img[i][j].v < 0.15)
			{
				img[i][j].v = 0;
				img[i][j].s = 0;
				img[i][j].h = 0;
			}
			else if (img[i][j].v > 0.8 && img[i][j].s < 0.1)
			{
				img[i][j].v = 1;
				img[i][j].s = 0;
				img[i][j].h = 0;
			}
		}
	}
}

//
void ZImage::RegionGrowingOriginal()
{
	int i, j;
	objectcount = 0;
	pixel = w * h;
	memset(objectaveragecolor, 0, sizeof(objectaveragecolor));
	memset(objectarea, 0, sizeof(objectarea));
	memset(objectcenterx, 0, sizeof(objectcenterx));
	memset(objectcentery, 0, sizeof(objectcentery));
	while (pixel > 0)
	{
		objectcount++;
		for (i = 0; i < h; i++)
		{
			for (j = 0; j < w; j++)
			{
				if (object[i][j] == 0)
				{
					break;
				}
			}
			if (j < w)
			{
				break;
			}
		}
		pixel--;
		object[i][j] = objectcount;
		objectaveragecolor[objectcount].x = img[i][j].x;
		objectaveragecolor[objectcount].y = img[i][j].y;
		objectaveragecolor[objectcount].z = img[i][j].z;
		objectarea[objectcount] = 1;
		objectcenterx[objectcount] = i;
		objectcentery[objectcount] = j;
		RegionGrowingDFS(i, j, objectcount);
	}
}

//
void ZImage::RegionGrowingIteration()
{
	int i, j;
	for (i = 1; i <= objectcount; i++)
	{
		if (object[objectcenterx[i] / objectarea[i]][objectcentery[i] / objectarea[i]] != i)
		{
			return;
		}
	}
	for (i = 1; i < objectcount; i++)
	{
		for (j = objectcount; j > i; j--)
		{
			if (objectarea[j] > objectarea[i])
			{
				int temp;
				temp = objectarea[j];
				objectarea[j] = objectarea[i];
				objectarea[i] = temp;
				temp = objectcenterx[j];
				objectcenterx[j] = objectcenterx[i];
				objectcenterx[i] = temp;
				temp = objectcentery[j];
				objectcentery[j] = objectcentery[i];
				objectcentery[i] = temp;
			}
		}
	}
	for (i = 1; i <= objectcount; i++)
	{
		objectcenterx[i] /= objectarea[i];
		objectcentery[i] /= objectarea[i];
	}
	for (j = 0; j < h; j++)
	{
		memset(object[j], 0, w*sizeof(int));
	}
	memset(objectaveragecolor, 0, sizeof(objectaveragecolor));
	for (i = 1; i <= objectcount; i++)
	{
		object[objectcenterx[i]][objectcentery[i]] = i;
		objectaveragecolor[i].x = img[objectcenterx[i]][objectcentery[i]].x;
		objectaveragecolor[i].y = img[objectcenterx[i]][objectcentery[i]].y;
		objectaveragecolor[i].z = img[objectcenterx[i]][objectcentery[i]].z;
		objectarea[i] = 1;
		RegionGrowingDFS(objectcenterx[i], objectcentery[i], i);
	}
}

void ZImage::RegionGrowingDFS(int x, int y, int &id)
{
	if (x > 0)
	{
		if (object[x - 1][y] == 0 && 
			(img[x - 1][y].x - objectaveragecolor[id].x) * 
			(img[x - 1][y].x - objectaveragecolor[id].x) + 
			(img[x - 1][y].y - objectaveragecolor[id].y) * 
			(img[x - 1][y].y - objectaveragecolor[id].y) + 
			(img[x - 1][y].z - objectaveragecolor[id].z) * 
			(img[x - 1][y].z - objectaveragecolor[id].z) <= 0.09)
		{
			pixel--;
			object[x - 1][y] = id;
			objectaveragecolor[id].x = (objectaveragecolor[id].x * objectarea[id] + img[x - 1][y].x) / (objectarea[id] + 1);
			objectaveragecolor[id].y = (objectaveragecolor[id].y * objectarea[id] + img[x - 1][y].y) / (objectarea[id] + 1);
			objectaveragecolor[id].z = (objectaveragecolor[id].z * objectarea[id] + img[x - 1][y].z) / (objectarea[id] + 1);
			objectarea[id]++;
			objectcenterx[id] += (x - 1);
			objectcentery[id] += y;
			RegionGrowingDFS(x - 1, y, id);
		}
	}
	if (y > 0)
	{
		if (object[x][y - 1] == 0 && 
			(img[x][y - 1].x - objectaveragecolor[id].x) *
			(img[x][y - 1].x - objectaveragecolor[id].x) +
			(img[x][y - 1].y - objectaveragecolor[id].y) *
			(img[x][y - 1].y - objectaveragecolor[id].y) +
			(img[x][y - 1].z - objectaveragecolor[id].z) *
			(img[x][y - 1].z - objectaveragecolor[id].z) <= 0.09)
		{
			pixel--;
			object[x][y - 1] = id;
			objectaveragecolor[id].x = (objectaveragecolor[id].x * objectarea[id] + img[x][y - 1].x) / (objectarea[id] + 1);
			objectaveragecolor[id].y = (objectaveragecolor[id].y * objectarea[id] + img[x][y - 1].y) / (objectarea[id] + 1);
			objectaveragecolor[id].z = (objectaveragecolor[id].z * objectarea[id] + img[x][y - 1].z) / (objectarea[id] + 1);
			objectarea[id]++;
			objectcenterx[id] += x;
			objectcentery[id] += (y - 1);
			RegionGrowingDFS(x, y - 1, id);
		}
	}
	if (x < h - 1)
	{
		if (object[x + 1][y] == 0 && 
			(img[x + 1][y].x - objectaveragecolor[id].x) *
			(img[x + 1][y].x - objectaveragecolor[id].x) +
			(img[x + 1][y].y - objectaveragecolor[id].y) *
			(img[x + 1][y].y - objectaveragecolor[id].y) +
			(img[x + 1][y].z - objectaveragecolor[id].z) *
			(img[x + 1][y].z - objectaveragecolor[id].z) <= 0.09)
		{
			pixel--;
			object[x + 1][y] = id;
			objectaveragecolor[id].x = (objectaveragecolor[id].x * objectarea[id] + img[x + 1][y].x) / (objectarea[id] + 1);
			objectaveragecolor[id].y = (objectaveragecolor[id].y * objectarea[id] + img[x + 1][y].y) / (objectarea[id] + 1);
			objectaveragecolor[id].z = (objectaveragecolor[id].z * objectarea[id] + img[x + 1][y].z) / (objectarea[id] + 1);
			objectarea[id]++;
			objectcenterx[id] += (x + 1);
			objectcentery[id] += y;
			RegionGrowingDFS(x + 1, y, id);
		}
	}
	if (y < w - 1)
	{
		if (object[x][y + 1] == 0 && 
			(img[x][y + 1].x - objectaveragecolor[id].x) *
			(img[x][y + 1].x - objectaveragecolor[id].x) +
			(img[x][y + 1].y - objectaveragecolor[id].y) *
			(img[x][y + 1].y - objectaveragecolor[id].y) +
			(img[x][y + 1].z - objectaveragecolor[id].z) *
			(img[x][y + 1].z - objectaveragecolor[id].z) <= 0.09)
		{
			pixel--;
			object[x][y + 1] = id;
			objectaveragecolor[id].x = (objectaveragecolor[id].x * objectarea[id] + img[x][y + 1].x) / (objectarea[id] + 1);
			objectaveragecolor[id].y = (objectaveragecolor[id].y * objectarea[id] + img[x][y + 1].y) / (objectarea[id] + 1);
			objectaveragecolor[id].z = (objectaveragecolor[id].z * objectarea[id] + img[x][y + 1].z) / (objectarea[id] + 1);
			objectarea[id]++;
			objectcenterx[id] += x;
			objectcentery[id] += (y + 1);
			RegionGrowingDFS(x, y + 1, id);
		}
	}
}

void ZImage::GetFeature()
{
	memset(objectx2, 0, sizeof(objectx2));
	memset(objecty2, 0, sizeof(objecty2));
	memset(objectxy, 0, sizeof(objectxy));
	for (int i = 1; i <= objectcount; i++)
	{
		objectcenterx[i] /= objectarea[i];
		objectcentery[i] /= objectarea[i];
	}
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (object[i][j] != 0)
			{
				objectx2[object[i][j]] += ((i - objectcenterx[object[i][j]]) * (i - objectcenterx[object[i][j]]));
				objecty2[object[i][j]] += ((j - objectcentery[object[i][j]]) * (j - objectcentery[object[i][j]]));
				objectxy[object[i][j]] += ((i - objectcenterx[object[i][j]]) * (j - objectcentery[object[i][j]]));
			}
		}
	}
	for (int i = 1; i < objectcount; i++)
	{
		for (int j = objectcount; j > i; j--)
		{
			if (objectarea[j] > objectarea[i])
			{
				int temp;
				temp = objectarea[j];
				objectarea[j] = objectarea[i];
				objectarea[i] = temp;
				temp = objectcenterx[j];
				objectcenterx[j] = objectcenterx[i];
				objectcenterx[i] = temp;
				temp = objectcentery[j];
				objectcentery[j] = objectcentery[i];
				objectcentery[i] = temp;
				double tempd;
				tempd = objectx2[j];
				objectx2[j] = objectx2[i];
				objectx2[i] = tempd;
				tempd = objecty2[j];
				objecty2[j] = objecty2[i];
				objecty2[i] = tempd;
				tempd = objectxy[j];
				objectxy[j] = objectxy[i];
				objectxy[i] = tempd;
				tempd = objectaveragecolor[i].x;
				objectaveragecolor[i].x = objectaveragecolor[j].x;
				objectaveragecolor[j].x = tempd;
				tempd = objectaveragecolor[i].y;
				objectaveragecolor[i].y = objectaveragecolor[j].y;
				objectaveragecolor[j].y = tempd;
				tempd = objectaveragecolor[i].z;
				objectaveragecolor[i].z = objectaveragecolor[j].z;
				objectaveragecolor[j].z = tempd;
			}
		}
	}
}

void ZImage::OutputFeature(ofstream& output)
{
	for (int i = 1; i <= objectcount; i++)
	{
		if (objectarea[i] > w * h * 0.01)
		{
			output << objectaveragecolor[i].x << " " << objectaveragecolor[i].y << " " << objectaveragecolor[i].z << " ";
			output << objectcenterx[i] * 1.0 / h << " " << objectcentery[i] * 1.0 / w << " ";
			output << objectarea[i] * 1.0 / h / w << " ";
			if (w > h)
			{
				output << sqrt((objectx2[i] + objecty2[i]) * 1.0 / objectarea[i]) / w << " ";
			}
			else
			{
				output << sqrt((objectx2[i] + objecty2[i]) * 1.0 / objectarea[i]) / h << " ";
			}
			output << (objectx2[i] + objecty2[i] - sqrt(1.0 * (objectx2[i] - objecty2[i]) * (objectx2[i] - objecty2[i]) + 4.0 * objectxy[i] * objectxy[i])) / (objectx2[i] + objecty2[i] + sqrt(1.0 * (objectx2[i] - objecty2[i]) * (objectx2[i] - objecty2[i]) + 4.0 * objectxy[i] * objectxy[i]))
					<< " ";
		}
	}
    output << endl;
}
