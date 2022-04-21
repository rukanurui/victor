#include "particle.h"
#include <cstdlib>      // srand,rand
#include <time.h>

void particle::createblue(float x, float y, float vecx, float vecy)
{
	
	for (int i = 0; i < 100; i++)
	{

		if (PARTb[i].flag == 0)
		{

			int pcount = rand()%10+1;

			PARTb[i].x = x;
			PARTb[i].y = y;

			// ˆÚ“®—Í‚ðÝ’è

			PARTb[i].velx = (double)rand()/RAND_MAX/5 ;
			PARTb[i].vely = (double)rand() /RAND_MAX/5 ;
	

			//•ûŒü‚ðÝ’è

			if (pcount >= 4)
			{
				PARTb[i].velx *= -1;
			}
			if (pcount % 2 == 0)
			{
				PARTb[i].vely *= -1;
			}

			PARTb[i].flag = 1;
		}
	}
}

void particle::createred(float x, float y, float vecx, float vecy)
{

	for (int i = 0; i < 100; i++)
	{

		if (PARTr[i].flag == 0)
		{

			int pcount = rand() % 10 + 1;

			PARTr[i].x = x;
			PARTr[i].y = y;

			// ˆÚ“®—Í‚ðÝ’è

			PARTr[i].velx = (double)rand() / RAND_MAX / 5;
			PARTr[i].vely = (double)rand() / RAND_MAX / 5;


			//•ûŒü‚ðÝ’è

			if (pcount >= 4)
			{
				PARTr[i].velx *= -1;
			}
			if (pcount % 2 == 0)
			{
				PARTr[i].vely *= -1;
			}

			PARTr[i].flag = 1;
		}
	}
}

void particle::moveblue(float x, float y, float velx, float vely)
{
	for (int i = 0; i < 100; i++)
	{
		// ˆÊ’u‚ðˆÚ“®—Í‚É‰ž‚¶‚Ä‚¸‚ç‚·
		PARTb[i].y += PARTb[i].vely;
		PARTb[i].x += PARTb[i].velx;
	}
}

void particle::movered(float x, float y, float velx, float vely)
{

	for (int i = 0; i < 100; i++)
	{

		// ˆÊ’u‚ðˆÚ“®—Í‚É‰ž‚¶‚Ä‚¸‚ç‚·		
		PARTr[i].y += PARTr[i].vely;
		PARTr[i].x += PARTr[i].velx;
	}
}

void particle::Initialize()
{
	srand((unsigned)time(NULL));

	memset(PARTb, 0, sizeof(PARTb));

	for (int i = 0; i < 100; i++)
	{
		PARTb[i] = { 0,0,0,0,0,9.8/60};
	}

	for (int i = 0; i < 100; i++)
	{
		PARTr[i] = { 0,0,0,0,0,9.8 / 60 };
	}
}

void particle::Update(int flag)
{
	/*if (flag==1)
	{
		for (int i = 0; i < 100; i++)
		{
			createblue(x,  y,  vecx, vecy);
		}
	}*/

}

void particle::Finalizeblue(int& flag)
{
	for (int i = 0; i < 100; i++)
	{
		PARTb[i].count++;

		if (PARTb[i].count >= 10000)
		{
			for (int i = 0; i < 100; i++)
			{
				PARTb[i] = { 0,0,0,0,0, 9.8 / 60,0 };
				flag = 0;
			}
		}
	}
}

void particle::Finalizered(int& flag)
{
	for (int i = 0; i < 100; i++)
	{
		PARTr[i].count++;

		if (PARTr[i].count >= 10000)
		{
			for (int i = 0; i < 100; i++)
			{
				PARTr[i] = { 0,0,0,0,0, 9.8 / 60,0 };
				flag = 0;
			}
		}
	}
}
