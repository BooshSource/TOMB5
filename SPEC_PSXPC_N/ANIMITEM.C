#include "ANIMITEM.H"

#include "3D_GEN.H"
#include "CONTROL.H"
#include "LOAD_LEV.H"
#include "DRAW.H"
#include "CAMERA.H"
#include "SETUP.H"
#include "DRAWOBJ.H"
#include "MATHS.H"
#include "MISC.H"
#include "LIGHT.H"

#include "GTEREG.H"
#include <assert.h>

void GetBounds_AI(int* t0, int* a2, int* a3, int* t1, int* t2, int* v0, int* a0, int* a1, int* t3, int* t4, int* t5)//8139C
{
	if (*t0 < *a2)
	{
		*a2 = *t0;
	}

	//loc_813AC
	if (*t0 >= *a3)
	{
		*a3 = *t0;
	}

	//loc_813B8
	if (*t1 < *a2)
	{
		*a2 = *t1;
	}

	//loc_813C4
	if (*t1 >= *a3)
	{
		*a3 = *t1;
	}

	if (*t2 < *a2)
	{
		*a3 = *t2;
	}

	//loc_813DC
	*t0 <<= 16;
	if (*t2 >= *a3)
	{
		*a3 = *t2;
	}

	//loc_813E8
	*t1 <<= 16;
	*t2 <<= 16;

	if (*t0 < *a0)
	{
		*a0 = *t0;
	}

	if (*t0 >= *a1)
	{
		*a1 = *t0;
	}

	if (*t1 < *a0)
	{
		*a0 = *t1;
	}

	if (*t1 >= *a1)
	{
		*a1 = *t1;
	}

	if (*t2 < *a0)
	{
		*a0 = *t2;
	}

	if (*t2 >= *a1)
	{
		*a1 = *t2;
	}

	if (*t3 < 0x5000)
	{
		v0[0]++;
	}

	if (*t4 < 0x5000)
	{
		v0[0]++;
	}

	if (*t5 < 0x5000)
	{
		v0[0]++;
	}
}

void mLoadMatrix_AI(int* a0, int* fp)//81C18(<)
{
	R11 = (a0[0] & 0xFFFF);
	R12 = (a0[0] >> 16) & 0xFFFF;
	R13 = (a0[1] & 0xFFFF);
	R21 = (a0[1] >> 16) & 0xFFFF;
	R22 = (a0[2] & 0xFFFF);
	R23 = (a0[2] >> 16) & 0xFFFF;
	R31 = (a0[3] & 0xFFFF);
	R32 = (a0[3] >> 16) & 0xFFFF;
	R33 = (a0[4] & 0xFFFF);
	TRX = a0[5];
	TRY = a0[6];
	TRZ = a0[7];

	fp[20] = (int)a0;
}

void mmPushMatrix_AI(int* fp)
{
	int* a0 = (int*)fp[20];
	a0 += 8;
	a0[0] = (R11 & 0xFFFF) | ((R12 & 0xFFFF) << 16);
	a0[1] = (R13 & 0xFFFF) | ((R21 & 0xFFFF) << 16);
	a0[2] = (R22 & 0xFFFF) | ((R23 & 0xFFFF) << 16);
	a0[3] = (R31 & 0xFFFF) | ((R32 & 0xFFFF) << 16);
	a0[4] = R33;
	a0[5] = TRX;
	a0[6] = TRY;
	a0[7] = TRZ;

	fp[20] = (int)a0;
}


void mmPopMatrix_AI(int* fp)//81C0C(<)
{
	mLoadMatrix_AI((int*)(fp[20] - 0x20), fp);
}

void SetRotation_AI(int* fp, int t0, int t1, int t2, int t3, int t4)
{
	int a0 = fp[20];

	R11 = t0 & 0xFFFF;
	R12 = (t0 >> 16) & 0xFFFF;
	R13 = t1 & 0xFFFF;
	R21 = (t1 >> 16) & 0xFFFF;
	R22 = t2 & 0xFFFF;
	R23 = (t2 >> 16) & 0xFFFF;
	R31 = t3 & 0xFFFF;
	R32 = (t3 >> 16) & 0xFFFF;
	R33 = t4 & 0xFFFF;

	((int*)a0)[0] = t0;
	((int*)a0)[1] = t1;
	((int*)a0)[2] = t2;
	((int*)a0)[3] = t3;
	((int*)a0)[4] = t4;
}


void mRotY_AI(int ry, int* fp)//0x81858
{
	int t4 = 0;
	int t1 = 0;
	int t5 = 0;
	int t7 = 0;
	int t6 = 0;
	int t2 = 0;
	int t0 = 0;
	int t3 = 0;

	ry = (ry >> 2) & 0x3FFC;
	if (ry == 0)
	{
		return;
	}

	//t0 = 0x9A8C8 rcossin_tbl
	//loc_81870
	t5 = ((int*)&rcossin_tbl[ry >> 1])[0];
	t7 = 0xFFFF0000;
	t6 = (t5 >> 16) & 0xFFFF;
	t5 &= 0xFFFF;
	t2 = -t5;
	VX0 = t6;
	VY0 = (t6 >> 16) & 0xFFFF;
	VZ0 = t2;

	t0 = (R11 & 0xFFFF) | ((R12 & 0xFFFF) << 16);
	t2 = (R22 & 0xFFFF) | ((R23 & 0xFFFF) << 16);
	t3 = (R31 & 0xFFFF) | ((R32 & 0xFFFF) << 16);

	docop2(0x486012);

	VX1 = t5 & 0xFFFF;
	VY1 = (t5 >> 16) & 0xFFFF;
	VZ1 = t6 & 0xFFFF;

	t0 &= t7;
	t2 &= 0xFFFF;
	t3 &= t7;
	t4 = MAC1;
	t1 = MAC2;
	t5 = MAC3;

	docop2(0x48E012);

	t4 &= 0xFFFF;
	t0 |= t4;
	t1 <<= 16;
	t5 &= 0xFFFF;
	t3 |= t5;

	t5 = MAC1;
	t6 = MAC2;
	t4 = MAC3;

	t5 &= 0xFFFF;
	t1 |= t5;
	t6 <<= 16;
	t2 |= t6;

	SetRotation_AI(fp, t0, t1, t2, t3, t4);
}

void mRotX_AI(int rx, int* fp)//0x817B0
{
	int t5 = 0;
	int t6 = 0;
	int t7 = 0;
	int t0 = 0;
	int t1 = 0;
	int t3 = 0;
	int t4 = 0;
	int t2 = 0;

	rx = (rx >> 2) & 0x3FFC;
	if (rx == 0)
	{
		return;
	}

	//loc_81870
	t5 = ((int*)&rcossin_tbl[rx >> 1])[0];
	t7 = 0xFFFF0000;
	t6 = t7 & t5;

	VX0 = t6 & 0xFFFF;
	VY0 = (t6 >> 16) & 0xFFFF;
	VZ0 = t5;

	t0 = (R11 & 0xFFFF) | ((R12 & 0xFFFF) << 16);
	t1 = (R13 & 0xFFFF) | ((R21 & 0xFFFF) << 16);
	t3 = (R31 & 0xFFFF) | ((R32 & 0xFFFF) << 16);

	docop2(0x486012);

	t6 = t5 >> 16;
	t5 <<= 16;
	t5 = -t5;
	VX1 = t5 & 0xFFFF;
	VY1 = (t5 >> 16) & 0xFFFF;
	VZ1 = t6;

	t0 &= 0xFFFF;
	t1 &= t7;
	t3 &= 0xFFFF;

	t4 = MAC1;
	t2 = MAC2;
	t5 = MAC3;

	docop2(0x48E012);

	t4 <<= 16;
	t0 |= t4;
	t2 &= 0xFFFF;
	t5 <<= 16;
	t3 |= t5;

	t5 = MAC1;
	t6 = MAC2;
	t4 = MAC3;

	t5 &= 0xFFFF;
	t1 |= t5;
	t6 <<= 16;
	t2 |= t6;

	SetRotation_AI(fp, t0, t1, t2, t3, t4);
}

void mRotZ_AI(int rz, int* fp)//0x81918
{
	int a0 = 0;
	int t6 = 0;
	int t0 = 0;
	int t7 = 0;
	int t1 = 0;
	int t2 = 0;
	int t4 = 0;
	int t3 = 0;
	int t5 = 0;

	rz = (rz >> 2) & 0x3FFC;
	if (rz == 0)
	{
		return;
	}

	//loc_81870
	t0 = ((int*)&rcossin_tbl[rz >> 1])[0];
	t7 = 0xFFFF0000;
	t1 = t0 >> 16;
	t2 = t0 << 16;
	t1 |= t2;
	VX0 = t1 & 0xFFFF;
	VY0 = (t1 >> 16) & 0xFFFF;
	VZ0 = 0;

	t1 = (R13 & 0xFFFF) | ((R21 & 0xFFFF) << 16);
	t2 = (R22 & 0xFFFF) | ((R23 & 0xFFFF) << 16);
	t4 = R33;

	docop2(0x486012);

	t3 = t0 & t7;
	t0 &= 0xFFFF;
	t0 = -t0;
	t0 &= 0xFFFF;
	t0 |= t3;

	VX1 = t0 & 0xFFFF;
	VY1 = (t0 >> 16) & 0xFFFF;
	VZ1 = 0;

	t1 &= 0xFFFF;
	t0 = MAC1;
	t5 = MAC2;
	t3 = MAC3;

	docop2(0x48E012);

	t2 &= t7;
	t0 &= 0xFFFF;
	t5 <<= 16;
	t1 |= t5;
	t3 &= 0xFFFF;
	t5 = MAC1;
	t6 = MAC2;
	a0 = MAC3;

	t5 <<= 16;
	t0 |= t5;
	t6 &= 0xFFFF;
	t2 |= t6;
	a0 <<= 16;
	t3 |= a0;

	SetRotation_AI(fp, t0, t1, t2, t3, t4);
}

int GetFrames_AI(struct ITEM_INFO* item /*s3*/, int* fp)//81468
{
	struct ANIM_STRUCT* anim = NULL;//$t0
	int t1 = 0;
	int t2 = 0;
	int t3 = 0;
	short* t4 = NULL;
	short* t5 = NULL;

	anim = &((struct ANIM_STRUCT*)fp[39])[item->anim_number];

	fp[23] = anim->interpolation & 0xFF;
	t1 = (item->frame_number - anim->frame_base) / (anim->interpolation & 0xFF);
	t2 = (item->frame_number - anim->frame_base) % (anim->interpolation & 0xFF);

	t3 = t1 * (anim->interpolation >> 8);
	t4 = &anim->frame_ptr[t3];
	fp[30] = (int)t4;
	t5 = &anim->frame_ptr[t3 + (anim->interpolation >> 8)];
	fp[31] = (int)t5;

	if (t2 == 0)
	{
		return 0;
	}

	//loc_814D8
	t3 = t1 * (anim->interpolation & 0xFF);
	if (anim->frame_end < t3 + (anim->interpolation & 0xFF))
	{
		fp[23] = anim->frame_end - ((t3 + (anim->interpolation & 0xFF)) - (anim->interpolation & 0xFF));
	}

	return t2;
}

void mTranslateXYZ_AI(int tx, int ty, int tz, int* fp)//81AB0
{
	int t0 = 0;
	int t1 = 0;
	int t2 = 0;
	int t3 = 0;
	int t5 = 0;
	int v0 = 0;
	int t4 = ty >> 15;

	if (ty < 0)
	{
		ty = -ty;
		t4 = ty >> 15;
		ty &= 0x7FFF;
		t4 = -t4;
		ty = -ty;

	}
	else
	{
		//loc_81AD0
		ty &= 0x7FFF;
	}

	//loc_81AD4
	t5 = tz >> 15;
	if (tz < 0)
	{
		tz = -tz;
		t5 = tz >> 15;
		tz &= 0x7FFF;
		t5 = -t5;
		tz = -tz;
	}
	else
	{
		//loc_81AF4
		tz &= 0x7FFF;
	}

	//loc_81AF8
	t3 = tx >> 15;
	if (tx < 0)
	{
		tx = -tx;
		t3 = tx >> 15;
		tx &= 0x7FFF;
		t3 = -t3;
		tx = -tx;
	}
	else
	{
		//loc_81B18
		tx &= 0x7FFF;
	}

	//loc_81B1C
	IR1 = t3;
	IR2 = t4;
	IR3 = t5;

	v0 = fp[20];

	docop2(0x41E012);

	t3 = MAC1;
	t4 = MAC2;
	t5 = MAC3;

	IR1 = tx;
	IR2 = ty;
	IR3 = tz;

	docop2(0x498012);

	t0 = t3 << 3;
	if (t3 < 0)
	{
		t3 = -t3;
		t3 <<= 3;
		t0 = -t3;
	}//loc_81B60

	t1 = t4 << 3;
	if (t4 < 0)
	{
		t4 = -t4;
		t4 <<= 3;
		t1 = -t4;
	}

	//loc_81B74
	t2 = t5 << 3;
	if (t5 < 0)
	{
		t5 = -t5;
		t5 <<= 3;
		t2 = -t5;
	}
	//loc_81B88
	t3 = MAC1;
	t4 = MAC2;
	t5 = MAC3;

	t0 += t3;
	t1 += t4;
	t2 += t5;

	TRX = t0;
	TRY = t1;
	TRZ = t2;

	((int*)v0)[5] = t0;
	((int*)v0)[6] = t1;
	((int*)v0)[7] = t2;
}


void mTranslateAbsXYZ_AI(int tx, int ty, int tz, int* fp)
{
	TRX = 0;
	TRY = 0;
	TRZ = 0;
	tx -= fp[27];
	ty -= fp[28];
	tz -= fp[29];

	mTranslateXYZ_AI(tx, ty, tz, fp);
}

void mRotYXZ_AI(int y, int x, int z, int* fp)//818FC
{
	mRotY_AI(y, fp);
	mRotX_AI(x, fp);
	mRotZ_AI(z, fp);
}

void calc_animating_item_clip_window(struct ITEM_INFO* item /*s3*/, unsigned short* s2, int* fp)//80DD8
{
	int* s1 = (int*)fp[25];
	int t3 = 0;
	int t2 = 0;
	int t1 = 0;
	int t0 = 0;
	int s5 = 0;
	int s4 = 0;
	int s7 = 0;
	int v0 = 0;
	int v1 = 0;
	int a0 = 0;
	int t9 = 0;
	int t8 = 0;
	int t4 = 0;
	int s22 = 0;
	int* t5 = NULL;
	int a2 = 0;
	int t6 = 0;
	int t55 = 0;
	int a1 = 0;
	int t7 = 0;
	int at = 0;
	int a3 = 0;

	if ((unsigned)(item->object_number - 0x1A0) >= 0x1F && (unsigned)(item->object_number - 0x11C) >= 0x20)
	{
		//a1 = 0x1000
		R11 = 4096;
		R12 = 0;
		R13 = 0;
		R21 = 0;
		R22 = 4096;
		R23 = 0;
		R31 = 0;
		R32 = 0;
		R33 = 4096;

		fp[20] += 0x20;
		mRotYXZ_AI(item->pos.y_rot, item->pos.x_rot, item->pos.z_rot, fp);

		TRX = 0;
		TRY = 0;
		TRZ = 0;

		//t5 = 0x1f800000
		((short*)fp)[0] = s2[0];///@0x1F800000
		((short*)fp)[1] = s2[2];
		((short*)fp)[2] = s2[4];

		((short*)fp)[4] = s2[1];
		((short*)fp)[5] = s2[2];
		((short*)fp)[6] = s2[4];

		((short*)fp)[8] = s2[1];
		((short*)fp)[9] = s2[3];
		((short*)fp)[10] = s2[4];

		((short*)fp)[12] = s2[0];
		((short*)fp)[13] = s2[3];
		((short*)fp)[14] = s2[4];

		((short*)fp)[16] = s2[0];
		((short*)fp)[17] = s2[2];
		((short*)fp)[18] = s2[5];

		((short*)fp)[20] = s2[1];
		((short*)fp)[21] = s2[2];
		((short*)fp)[22] = s2[5];

		((short*)fp)[24] = s2[1];
		((short*)fp)[25] = s2[3];
		((short*)fp)[26] = s2[5];

		((short*)fp)[28] = s2[0];
		((short*)fp)[29] = s2[3];
		((short*)fp)[30] = s2[5];

		s5 = 32767;
		s4 = -32767;
		s7 = 32767;
		t9 = -32767;
		t8 = 32767;
		s22 = -32767;
		t4 = 8;

		 t5 = &fp[0];

		//loc_80ED4
		do
		{
			VX0 = t5[0] & 0xFFFF;
			VY0 = (t5[0] >> 16) & 0xFFFF;
			VZ0 = t5[1];

			t4--;

			docop2(0x480012);
			v1 = MAC1;
			v0 = MAC2;
			a2 = MAC3;

			if (v1 < s5)
			{
				s5 = v1;
			}

			if (s4 < v1)
			{
				s4 = v1;
			}

			if (v0 < s7)
			{
				s7 = v0;
			}

			if (t9 < v0)
			{
				t9 = v0;
			}

			if (a2 < t8)
			{
				t8 = a2;
			}

			if (s22 < a2)
			{
				s22 = a2;
			}

			t5 += 2;

		} while (t4 != 0);

		mmPopMatrix_AI(fp);

		v0 = item->pos.x_pos;
		v1 = item->pos.y_pos;
		a0 = item->pos.z_pos;

		s5 += v0;
		s4 += v0;
		s7 += v1;
		t9 += v1;
		t8 += a0;
		s22 += a0;

		t6 = s1[5] + 1024;
		t55 = s1[7] + 1024;

		a0 = t6 + ((((short*)s1)[21] - 2) << 10);
		a1 = t55 + ((((short*)s1)[20] - 2) << 10);

		t7 = s1[9];
		v1 = s1[8];

		if (s5 < t6 || a0 < s4 || s7 < t7 || v1 < t9 || t8 < t55 || a1 < s22)
		{
			//loc_80FE4
			t3 = s1[1];
			if (((short*)fp)[53] == item->room_number)
			{
				return;
			}

			if (((short*)fp)[53] == ((short*)fp)[52])
			{
				return;
			}

			t4 = ((short*)t3)[0];
			t3 += 2;

			if (t4 > 0)
			{
				//loc_8100C
				do
				{
					at = ((short*)t3)[0];
					v1 = ((short*)fp)[53];
					a1 = ((short*)t3)[4];

					if (at == v1)
					{
						a2 = ((short*)t3)[5];
						a3 = ((short*)t3)[6];
						v0 = ((short*)t3)[7];
						v1 = ((short*)t3)[8];
						a0 = ((short*)t3)[9];

						t2 = a1;
						t0 = a2;
						t1 = a3;

						if (v0 < a1)
						{
							t2 = v0;
						}
						else if (a1 < v0)
						{
							a1 = v0;
						}

						//loc_8105C
						if (v1 < t0)
						{
							t0 = v1;
						}
						else if (a2 < v1)
						{
							t0 = v1;
						}

						//loc_8107C
						if (a0 < t1)
						{
							t1 = a0;
						}
						else if (a3 < a0)
						{
							a3 = a0;
						}

						//loc_8109C
						v0 = ((short*)t3)[10];
						v1 = ((short*)t3)[11];
						a0 = ((short*)t3)[12];

						if (v0 < t2)
						{
							t2 = v0;
						}
						else if (a1 < v0)
						{
							a1 = v0;
						}

						if (v1 < t0)
						{
							t0 = v1;
						}
						else if (a2 < v1)
						{
							a2 = v1;
						}

						if (a0 < t1)
						{
							t1 = a0;
						}
						else if (a3 < a0)
						{
							a3 = a0;
						}

						//loc_81108
						v0 = ((short*)t3)[13];
						v1 = ((short*)t3)[14];
						a0 = ((short*)t3)[15];

						if (v0 < t2)
						{
							t2 = v0;
						}
						else if (a1 < v0)
						{
							a1 = v0;
						}

						if (v1 < t0)
						{
							t0 = v1;
						}
						else if (a2 < v1)
						{
							a2 = v1;
						}

						if (a0 < t1)
						{
							t1 = a0;
						}
						else if (a3 < a0)
						{
							a3 = a0;
						}

						//loc_81174
						at = t2 - 1024;
						t2 = at + t6;
						at = a1 - 1024;
						a1 = at + t6;
						t0 += t7;
						at = t1 - 1024;
						t1 = at + t55;
						at = a3 - 1024;
						a3 = at + t55;
						a2 += t7;

						if (s4 >= t2 && a1 >= t55 && t9 >= t0 && a2 >= s7 && s22 >= t1 && a3 >= t8)
						{
							//loc_811DC
							break;
						}

					}//loc_811D0
					t3 += 0x20;
				}while (--t4 > 0);
			}//loc_811DC

			if (t4 != 0)
			{
				return;
			}
		}//loc_811E4
	}//loc_811E4

	fp[36] = s1[14];
	fp[37] = s1[15];
}

int mClipBoundingBox_AI(unsigned short* a0, int* fp)//811FC
{
	int t0 = TRZ - 20480;
	int v0 = 0;
	int t5 = 0;
	int a00 = 0;
	int a1 = 0;
	int a2 = 0;
	int a3 = 0;
	int t3 = 0;
	int t1 = 0;
	int t4 = 0;
	int t2 = 0;
	int t7 = 0;
	unsigned int at = 0;
	int t9 = 0;
	int t8 = 0;
	int v1 = 0;

	if (t0 < 0)
	{
		t0 = a0[0];
		t3 = a0[1];
		t1 = a0[2] << 16;
		t4 = a0[3] << 16;
		t2 = a0[4];
		t7 = a0[5];
		at = t0 | t1;

		VX0 = at & 0xFFFF;
		VY0 = (at >> 16) & 0xFFFF;
		VZ0 = t2;

		at = t3 | t1;
		VX1 = at & 0xFFFF;
		VY1 = (at >> 16) & 0xFFFF;
		VZ1 = t2;

		at = t0 | t4;
		VX2 = at & 0xFFFF;
		VY2 = (at >> 16) & 0xFFFF;
		VZ2 = t2;

		docop2(0x280030);

		t9 = t3 | t4;
		t8 = t2;
		a00 = 0x7FFFFFFF;
		a1 = 0x81000000;
		a2 = 0x7FFFFFFF;
		a3 = 0x81000000;

		t0 = SXY0;
		t1 = SXY1;
		t2 = SXY2;
		t3 = SZ1;
		t4 = SZ2;
		t5 = SZ3;

		VZ0 = t7;
		VZ1 = t7;
		VZ2 = t7;

		docop2(0x280030);

		t3 -= 33;
		t4 -= 33;
		t5 -= 33;

		v0 = 0;
		GetBounds_AI(&t0, &a2, &a3, &t1, &t2, &v0, &a00, &a1, &t3, &t4, &t5);

		t0 = SXY0;
		t1 = SXY1;
		t2 = SXY2;
		t3 = SZ1 - 33;
		t4 = SZ2 - 33;
		t5 = SZ3 - 33;

		VX0 = t9 & 0xFFFF;
		VY0 = (t9 >> 16) & 0xFFFF;
		VZ0 = t8;

		VX1 = t9 & 0xFFFF;
		VY1 = (t9 >> 16) & 0xFFFF;

		docop2(0x280030);

		GetBounds_AI(&t0, &a2, &a3, &t1, &t2, &v0, &a00, &a1, &t3, &t4, &t5);

		t0 = SXY0;
		t1 = SXY1;
		t3 = SZ1 - 33;
		t4 = SZ2 - 33;
		t2 = t1;
		t5 = t4;
		GetBounds_AI(&t0, &a2, &a3, &t1, &t2, &v0, &a00, &a1, &t3, &t4, &t5);

		t0 = ((short*)fp)[73];
		t1 = ((short*)fp)[75];
		t2 = ((short*)fp)[72];
		t3 = ((short*)fp)[74];

		a00 >>= 16;
		a1 >>= 16;
		a2 >>= 16;
		a3 >>= 16;

		v1 = v0;

		if (v1 == 0 || t0 < a00 || t1 < a2 || a1 < t2 || a3 < t3)
			return 0;

		if (v1 < 9 || a00 < t2 || a2 < t3 || t0 < a1 || t1 < a3)
			return -1;

		v0 = 1;
	}
	//locret_81394
	return v0;
}

void InitInterpolation_AI(int* fp, int a0, int* a2)//81DF4
{
	int t0 = 0;
	int t1 = 0;
	int t2 = 0;
	int t3 = 0;
	int t4 = 0;
	int t5 = 0;
	int t6 = 0;
	int t7 = 0;

	fp[22] = a0;
	t0 = (R11 & 0xFFFF) | ((R12 & 0xFFFF) << 16);
	t1 = (R13 & 0xFFFF) | ((R21 & 0xFFFF) << 16);
	t2 = (R22 & 0xFFFF) | ((R23 & 0xFFFF) << 16);
	t3 = (R31 & 0xFFFF) | ((R32 & 0xFFFF) << 16);
	t4 = (R33 & 0xFFFF);
	t5 = TRX;
	t6 = TRY;
	t7 = TRZ;

	L11 = t0 & 0xFFFF;
	L12 = (t0 >> 16) & 0xFFFF;
	L13 = t1 & 0xFFFF;
	L21 = (t1 >> 16) & 0xFFFF;
	L22 = t2 & 0xFFFF;
	L23 = (t2 >> 16) & 0xFFFF;
	L31 = t3 & 0xFFFF;
	L32 = (t3 >> 16) & 0xFFFF;
	L33 = t4 & 0xFFFF;

	RBK = t5;
	GBK = t6;
	BBK = t7;

	fp[21] = (int)a2;

	a2[0] = t0;
	a2[1] = t1;
	a2[2] = t2;
	a2[3] = t3;
	a2[4] = t4;
	a2[5] = t5;
	a2[6] = t6;
	a2[7] = t7;
}

void iTranslateXYZ2_AI(int x/*a0*/, int y/*a1*/, int z/*a2*/, int x2/*a3*/, int* fp)//821DC
{
	int t5 = 0;
	int t4 = 0;
	int t3 = 0;
	int t0 = 0;
	int t1 = 0;
	int t2 = 0;
	int v0 = 0;
	int t6 = 0;
	int t7 = 0;
	int t8 = 0;

	mTranslateXYZ_AI(x, y, z, fp);

	y = fp[34];
	z = fp[35];

	t0 = x2 >> 15;
	if (t0 < 0)
	{
		x2 = -x2;
		t0 = x2 >> 15;
		x2 &= 0x7FFF;
		t0 = -t0;
		x2 = -x2;
	}
	else
	{
		x2 &= 0x7FFF;
	}

	//loc_82214
	t1 = y >> 15;
	if (y < 0)
	{
		y = -y;
		t1 = y >> 15;
		y &= 0x7FFF;
		t1 = -t1;
		y = -y;
	}
	else
	{
		y &= 0x7FFF;
	}

	//loc_82238
	t2 = z >> 15;
	if (z < 0)
	{
		z = -z;
		t2 = z >> 15;
		z &= 0x7FFF;
		t2 = -t2;
		z = -z;
	}
	else
	{
		z &= 0x7FFF;
	}

	IR1 = t0;
	IR2 = t1;
	IR3 = t2;

	docop2(0x43E012);

	v0 = fp[21];
	t6 = MAC1;

	IR1 = x2;
	IR2 = y;
	IR3 = z;

	t7 = MAC2;
	t8 = MAC3;

	docop2(0x4BE012);

	t3 = t6 << 3;
	if (t6 < 0)
	{
		t6 = -t6;
		t6 <<= 3;
		t3 = -t6;
	}

	t4 = t7 << 3;
	if (t7 < 0)
	{
		t7 = -t7;
		t7 <<= 3;
		t4 = -t7;
	}
	
	t5 = t8 << 3;
	if (t8 < 0)
	{
		t8 = -t8;
		t8 <<= 3;
		t5 = -t8;
	}

	//loc_822CC
	t6 = MAC1;
	t7 = MAC2;
	t8 = MAC3;

	t3 += t6;
	t4 += t7;
	t5 += t8;

	t0 = RBK;
	t1 = GBK;
	t2 = BBK;

	t0 += t3;
	t1 += t4;
	t2 += t5;

	RBK = t0;
	GBK = t1;
	BBK = t2;

	((int*)v0)[5] = t0;
	((int*)v0)[6] = t1;
	((int*)v0)[7] = t2;
}

void iTranslateXYZ_AI(int tx, int ty, int tz, int* fp)//821D0
{
	fp[34] = ty;
	fp[35] = tz;
	iTranslateXYZ2_AI(tx, ty, tz, tx, fp);
}

void mRotSuperPackedYXZ_AI(int* fp)//819FC
{
	int a0 = 0;
	int v00 = 0;
	unsigned short* a2 = (unsigned short*)fp[32];
	unsigned short v0 = *a2++;
	int at = v0 >> 14;

	if (at-- != 0)
	{
		fp[32] = (int)a2;

		if (at-- != 0)
		{
			if (at != 0)
			{
				mRotZ_AI((v0 & 0xFFF) << 4, fp);
				return;
			}
			//loc_81A34
			mRotY_AI((v0 & 0xFFF) << 4, fp);
			return;
		}//loc_81A3C
		mRotX_AI((v0 & 0xFFF) << 4, fp);
		return;
	}
	//loc_81A48
	at = *a2++;
	fp[32] = (int)a2;
	a0 = v0 << 16;
	a0 |= at;
	v00 = a0;

	mRotY_AI((v00 >> 4) & 0xFFC0, fp);
	mRotX_AI((v00 >> 14) & 0xFFC0, fp);
	mRotZ_AI((v00 & 0x3FF) << 6, fp);
}

void SetRotation_I_AI(int t0, int t1, int t2, int t3, int t4, int* fp)//82110
{
	int* a0 = (int*)fp[21];

	L11 = t0 & 0xFFFF;
	L12 = (t0 >> 16) & 0xFFFF;
	L13 = t1 & 0xFFFF;
	L21 = (t1 >> 16) & 0xFFFF;
	L22 = t2 & 0xFFFF;
	L23 = (t2 >> 16) & 0xFFFF;
	L31 = t3 & 0xFFFF;
	L32 = (t3 >> 16) & 0xFFFF;
	L33 = t4;

	a0[0] = t0;
	a0[1] = t1;
	a0[2] = t2;
	a0[3] = t3;
	a0[4] = t4;
}

void iRotY_AI(int ry, int* fp)
{
	int t5 = 0;
	int t7 = 0;
	int t6 = 0;
	int t2 = 0;
	int t0 = 0;
	int t3 = 0;
	int t4 = 0;
	int t1 = 0;

	ry = (ry >> 2) & 0x3FFC;
	if (ry != 0)
	{
		t5 = ((int*)&rcossin_tbl[ry >> 1])[0];
		t7 = 0xFFFF0000;
		t6 = t5 >> 16;
		t5 &= 0xFFFF;
		t2 = -t5;

		VX0 = t6 & 0xFFFF;
		VY0 = (t6 >> 16) & 0xFFFF;
		VZ0 = t2;

		t0 = (L11 & 0xFFFF) | ((L12 & 0xFFFF) << 16);
		t2 = (L22 & 0xFFFF) | ((L23 & 0xFFFF) << 16);
		t3 = (L31 & 0xFFFF) | ((L32 & 0xFFFF) << 16);

		docop2(0x4A6012);

		VX1 = t5 & 0xFFFF;
		VY1 = (t5 >> 16) & 0xFFFF;
		VZ1 = t6;
		t0 &= t7;
		t2 &= 0xFFFF;
		t3 &= t7;
		t4 = MAC1;
		t1 = MAC2;
		t5 = MAC3;
		docop2(0x4AE012);
		t4 &= 0xFFFF;
		t0 |= t4;
		t1 <<= 16;
		t5 &= 0xFFFF;
		t3 |= t5;
		t5 = MAC1;
		t6 = MAC2;
		t4 = MAC3;
		t5 &= 0xFFFF;
		t1 |= t5;
		t6 <<= 16;
		t2 |= t6;

		SetRotation_I_AI(t0, t1, t2, t3, t4, fp);
	}
}

void iRotX_AI(int rx, int* fp)
{
	int t5 = 0;
	int t7 = 0;
	int t6 = 0;
	int t0 = 0;
	int t1 = 0;
	int t3 = 0;
	int t4 = 0;
	int t2 = 0;

	rx = (rx >> 2) & 0x3FFC;
	if (rx != 0)
	{
		t5 = ((int*)&rcossin_tbl[rx >> 1])[0];
		t7 = 0xFFFF0000;
		t6 = t7 & t5;

		VX0 = t6 & 0xFFFF;
		VY0 = (t6 >> 16) & 0xFFFF;
		VZ0 = t5;

		t0 = (L11 & 0xFFFF) | ((L12 & 0xFFFF) << 16);
		t1 = (L13 & 0xFFFF) | ((L21 & 0xFFFF) << 16);
		t3 = (L31 & 0xFFFF) | ((L32 & 0xFFFF) << 16);

		docop2(0x4A6012);

		t6 = t5 >> 16;
		t5 <<= 16;
		t5 = -t5;

		VX1 = t5 & 0xFFFF;
		VY1 = (t5 >> 16) & 0xFFFF;
		VZ1 = t6;

		t0 &= 0xFFFF;
		t1 &= t7;
		t3 &= 0xFFFF;

		t4 = MAC1;
		t2 = MAC2;
		t5 = MAC3;

		docop2(0x4AE012);

		t4 <<= 16;
		t0 |= t4;
		t2 &= 0xFFFF;
		t5 <<= 16;
		t3 |= t5;
		t5 = MAC1;
		t6 = MAC2;
		t4 = MAC3;
		t5 &= 0xFFFF;
		t1 |= t5;
		t6 <<= 16;
		t2 |= t6;

		SetRotation_I_AI(t0, t1, t2, t3, t4, fp);
	}
}

void iRotZ_AI(int rz, int* fp)
{
	int t0 = 0;
	int t7 = 0;
	int t1 = 0;
	int t2 = 0;
	int t4 = 0;
	int t3 = 0;
	int t5 = 0;
	int t6 = 0;
	int t8 = 0;

	rz = (rz >> 2) & 0x3FFC;
	if (rz != 0)
	{
		t0 = ((int*)&rcossin_tbl[rz >> 1])[0];
		t7 = 0xFFFF0000;
		t1 = t0 >> 16;
		t2 = t0 << 16;
		t1 |= t2;

		VX0 = t1 & 0xFFFF;
		VY0 = (t1 >> 16) & 0xFFFF;
		VZ0 = 0;

		t0 = (L13 & 0xFFFF) | ((L21 & 0xFFFF) << 16);
		t2 = (L22 & 0xFFFF) | ((L23 & 0xFFFF) << 16);
		t4 = (L33 & 0xFFFF);

		docop2(0x4A6012);
		t3 = t0 & t7;
		t0 &= 0xFFFF;
		t0 = -t0;
		t0 &= 0xFFFF;
		t0 |= t3;

		VX1 = t0 & 0xFFFF;
		VY1 = (t0 >> 16) & 0xFFFF;
		VZ1 = 0;

		t1 &= 0xFFFF;
		t0 = MAC1;
		t5 = MAC2;
		t3 = MAC3;

		docop2(0x4AE012);
		t2 &= t7;
		t0 &= 0xFFFF;
		t5 <<= 16;
		t1 |= t5;
		t3 &= 0xFFFF;
		t5 = MAC1;
		t6 = MAC2;
		t8 = MAC3;
		t5 <<= 16;
		t0 |= t5;
		t6 &= 0xFFFF;
		t2 |= t6;
		t8 <<= 16;
		t3 |= t8;

		SetRotation_I_AI(t0, t1, t2, t3, t4, fp);
	}
	//loc_82074
}

void iRotSuperPackedYXZ_AI(int* fp)//82140
{
	int a0 = 0;
	int a22 = 0;
	unsigned short* a2 = (unsigned short*)fp[33];
	unsigned short v0 = *a2++;
	int at = v0 >> 14;

	if (at-- != 0)
	{
		fp[33] = (int)a2;

		if (at-- != 0)
		{
			if (at != 0)
			{
				iRotZ_AI((v0 & 0xFFF) << 4, fp);
				return;
			}//loc_82178
			iRotY_AI((v0 & 0xFFF) << 4, fp);
			return;
		}
		//loc_82180
		iRotX_AI((v0 & 0xFFF) << 4, fp);
		return;
	}
	//loc_8218C
	at = *a2++;
	fp[33] = (int)a2;
	a0 = v0 << 16;
	a0 |= at;
	a22 = a0;

	iRotY_AI((a22 >> 4) & 0xFFC0, fp);
	iRotX_AI((a22 >> 14) & 0xFFC0, fp);
	iRotZ_AI((a22 << 6) & 0xFFC0, fp);
}

void InterpolateMatrix_AI(int v1, int* fp)
{
	int* a0 = (int*)fp[17];
	int v0 = fp[19];
	int* at = NULL;
	int a1 = 0;
	int a2 = 0;
	int t6 = 0;
	int t7 = 0;
	int a3 = 0;
	int t0 = 0;
	int t1 = 0;
	int t2 = 0;
	int t3 = 0;
	int t4 = 0;
	int att = 0;

	a0[0] = v1;
	at = &a0[9];
	v0 = 1;
	fp[19] = v0;
	fp[17] = (int)at;
	a0++;

	a2 = fp[20];
	a1 = fp[21];
	t6 = fp[23];
	t7 = fp[22];

	v0 = ((short*)a1)[0];
	v1 = ((short*)a2)[0];
	a3 = ((short*)a1)[1];
	t0 = ((short*)a2)[1];
	t1 = ((short*)a1)[2];
	t2 = ((short*)a2)[2];
	t3 = ((short*)a1)[3];
	t4 = ((short*)a2)[3];

	if (t6 == 2)
	{
		//loc_82384
		v0 = (v0 + v1) >> 1;
		a3 = (a3 + t0) >> 1;
		t1 = (t1 + t2) >> 1;
		t3 = (t3 + t4) >> 1;

		((short*)a0)[0] = v0;
		((short*)a3)[1] = a3;
		((short*)t1)[2] = t1;
		((short*)t3)[3] = t3;

		v0 = ((short*)a1)[4];
		v1 = ((short*)a2)[4];
		a3 = ((short*)a1)[5];
		t0 = ((short*)a2)[5];

		v0 = (v0 + v1) >> 1;
		a3 = (a3 + t0) >> 1;

		t1 = ((short*)a1)[6];
		t2 = ((short*)a2)[6];
		t3 = ((short*)a1)[7];
		t4 = ((short*)a2)[7];

		t1 = (t1 + t2) >> 1;
		t3 = (t3 + t4) >> 1;

		((short*)a0)[4] = v0;
		((short*)a0)[5] = a3;
		((short*)a0)[6] = t1;
		((short*)a0)[7] = t3;

		v0 = ((short*)a1)[8];
		v1 = ((short*)a2)[8];
		a3 = ((int*)a1)[5];
		t0 = ((int*)a2)[5];

		v0 = (v0 + v1) >> 1;
		a3 = (a3 + t0) >> 1;

		t1 = ((int*)a1)[6];
		t2 = ((int*)a2)[6];
		t3 = ((int*)a1)[7];
		t4 = ((int*)a2)[7];

		t1 = (t1 + t2) >> 1;
		t3 = (t3 + t4) >> 1;
	}
	else if (t7 == 2 || t6 == 4)
	{
		//loc_82448
		if (t7 == 1)
		{
			att = v0 - v1;
			v0 = att >> 2;
			v1 += v0;
			a3 = (a3 - t0) >> 2;
			t0 += a3;
			t1 = (t1 - t2) >> 2;
			t2 += t1;
			t3 = (t3 - t4) >> 2;
			t4 += t3;

			((short*)a0)[0] = v1;
			((short*)a0)[1] = t0;
			((short*)a0)[2] = t2;
			((short*)a0)[3] = t4;
			v0 = ((short*)a1)[4];
			v1 = ((short*)a2)[4];
			a3 = ((short*)a1)[5];
			t0 = ((short*)a2)[5];

			v0 = (v0 - v1) >> 2;
			v1 += v0;
			a3 = (a3 - t0) >> 2;
			t0 += a3;

			t1 = ((short*)a1)[6];
			t2 = ((short*)a2)[6];
			t3 = ((short*)a1)[7];
			t4 = ((short*)a2)[7];

			t1 = (t1 - t2) >> 2;
			t2 += t1;
			t3 = (t3 - t4) >> 2;
			t4 += t3;

			((short*)a0)[4] = v1;
			((short*)a0)[5] = t0;
			((short*)a0)[6] = t2;
			((short*)a0)[7] = t4;

			v0 = ((short*)a1)[8];
			v1 = ((short*)a2)[8];
			a3 = ((int*)a1)[5];
			t0 = ((int*)a2)[5];

			v0 = (v0 - v1) >> 2;
			v0 = v1 + v0;

			a3 = (a3 - t0) >> 2;
			a3 = t0 + a3;

			t1 = ((int*)a1)[6];
			t2 = ((int*)a2)[6];
			t3 = ((int*)a1)[7];
			t4 = ((int*)a2)[7];

			t1 = (t1 - t2) >> 2;
			t1 = t2 + t1;
			t3 = (t3 - t4) >> 2;
			t3 = t4 + t3;
		}
		else
		{
			//loc_82540
			att = v0 - v1;
			v1 = att >> 2;
			v0 -= v1;
			t0 = (a3 - t0) >> 2;
			a3 -= t0;
			t2 = (t1 - t2) >> 2;
			t1 -= t2;
			t4 = (t3 - t4) >> 2;
			t3 -= t4;

			((short*)a0)[0] = v0;
			((short*)a0)[1] = a3;
			((short*)a0)[2] = t1;
			((short*)a0)[3] = t3;
			v0 = ((short*)a1)[4];
			v1 = ((short*)a2)[4];
			a3 = ((short*)a1)[5];
			t0 = ((short*)a2)[5];

			v1 = (v0 - v1) >> 2;
			v0 -= v1;
			t0 = (a3 - t0) >> 2;
			a3 -= t0;

			t1 = ((short*)a1)[6];
			t2 = ((short*)a2)[6];
			t3 = ((short*)a1)[7];
			t4 = ((short*)a2)[7];

			t2 = (t1 - t2) >> 2;
			t1 -= t2;
			t4 = (t3 - t4) >> 2;
			t3 -= t4;

			((short*)a0)[4] = v0;
			((short*)a0)[5] = a3;
			((short*)a0)[6] = t1;
			((short*)a0)[7] = t3;

			v0 = ((short*)a1)[8];
			v1 = ((short*)a2)[8];
			a3 = ((int*)a1)[5];
			t0 = ((int*)a2)[5];

			v1 = (v0 - v1) >> 2;
			v0 -= v1;
			t0 = (a3 - t0) >> 2;
			a3 -= t0;

			t1 = ((int*)a1)[6];
			t2 = ((int*)a2)[6];
			t3 = ((int*)a1)[7];
			t4 = ((int*)a2)[7];

			t2 = (t1 - t2) >> 2;
			t1 -= t2;
			t4 = (t3 - t4) >> 2;
			t3 -= t4;
		}
	}

	((short*)a0)[8] = v0;
	((short*)a0)[5] = a3;
	((short*)a0)[6] = t1;
	((short*)a0)[7] = t3;
}

void iPushMatrix_AI(int* fp)//81E60
{
	int* a0 = (int*)fp[21];
	a0 += 8;
	a0[0] = L11 & 0xFFFF | ((L12 & 0xFFFF) << 16);
	a0[1] = L13 & 0xFFFF | ((L21 & 0xFFFF) << 16);
	a0[2] = L22 & 0xFFFF | ((L23 & 0xFFFF) << 16);
	a0[3] = L31 & 0xFFFF | ((L32 & 0xFFFF) << 16);
	a0[4] = L33 & 0xFFFF;
	a0[5] = RBK;
	a0[6] = GBK;
	a0[7] = BBK;
	fp[21] = (int)a0;
}

void iPopMatrix_AI(int* fp)//81EB0
{
	int* a0 = (int*)fp[20];
	int* a1 = (int*)fp[21];

	a0 -= 8;
	a1 -= 8;

	mLoadMatrix_AI(a0, fp);

	L11 = a1[0] & 0xFFFF;
	L12 = (a1[0] >> 16) & 0xFFFF;
	L13 = a1[1] & 0xFFFF;
	L21 = (a1[1] >> 16) & 0xFFFF;
	L22 = a1[2] & 0xFFFF;
	L23 = (a1[2] >> 16) & 0xFFFF;
	L31 = a1[3] & 0xFFFF;
	L32 = (a1[3] >> 16) & 0xFFFF;
	L33 = a1[4];
	RBK = a1[5];
	GBK = a1[6];
	BBK = a1[7];
	fp[21] = (int)a1;
}

void erk_interpolated(struct ITEM_INFO* item /*s3*/, struct object_info* object /*s6*/, int s0, short* s2, long* s5, short* s7, int* fp)//81C60
{
	int v11 = 0;
	short* v0 = NULL;
	short* v1 = NULL;

	int a0 = 0;
	int a1 = 0;
	int a2 = 0;
	int a3 = 0;
	int t0 = 0;
	int t1 = 0;
	int s4 = 0;

	InitInterpolation_AI(fp, s0, (int*)&fp[151]);

	v0 = (short*)fp[30];
	v1 = (short*)fp[31];

	a0 = v0[6];
	a1 = v0[7];
	a2 = v0[8];
	a3 = v1[6];
	t0 = v1[7];
	t1 = v1[8];

	v0 += 9;
	v1 += 9;

	fp[34] = t0;
	fp[35] = t1;
	fp[32] = (int)v0;
	fp[33] = (int)v1;

	iTranslateXYZ2_AI(a0, a1, a2, a3, fp);
	mRotSuperPackedYXZ_AI(fp);
	iRotSuperPackedYXZ_AI(fp);
	//gp = item->meshswap_meshbits
	//s3 = item->mesh_bits

	if ((item->mesh_bits & 1))
	{
		v11 = 0;
		if ((item->meshswap_meshbits & 1))
		{
			v11 = ((int*)s7)[1];
			InterpolateMatrix_AI(v11, fp);
		}//loc_81CD4
		else
		{
			v11 = ((int*)s7)[0];
			InterpolateMatrix_AI(v11, fp);
		}
	}
	//loc_81CDC
	s4 = object->nmeshes - 1;
	s7 += 4;
	if (object->nmeshes - 1 <= 0)
	{
		//81714
		assert(FALSE);//Unimplemented
	}

	//loc_81CF0
	do
	{
		if ((s5[0] & 0x1))
		{
			iPopMatrix_AI(fp);
		}
		//loc_81D0C
		if ((s5[0] & 0x2))
		{
			iPushMatrix_AI(fp);
		}

		//loc_81D20
		iTranslateXYZ_AI(s5[1], s5[2], s5[3], fp);
		mRotSuperPackedYXZ_AI(fp);
		iRotSuperPackedYXZ_AI(fp);

		if (s2 != NULL && (s5[0] & 0x1C))
		{
			if ((s5[0] & 0x8))
			{
				mRotY_AI(((short*)s2)[0], fp);
				iRotY_AI(((short*)s2)[0], fp);
				s2 += 1;
			}
			//loc_81D74
			if ((s5[0] & 0x4))
			{
				mRotX_AI(((short*)s2)[0], fp);
				iRotX_AI(((short*)s2)[0], fp);
				s2 += 1;
			}

			if ((s5[0] & 0x10))
			{
				mRotZ_AI(((short*)s2)[0], fp);
				iRotZ_AI(((short*)s2)[0], fp);
				s2 += 1;
			}
		}
		//loc_81DB8
		if ((1 << 1) & (item->mesh_bits))
		{
			int v11 = 0;
			if ((item->meshswap_meshbits & (1 << 1)))
			{
				v11 = ((int*)s7)[1];
			}
			else
			{
				v11 = ((int*)s7)[0];
			}
			//loc_81DD4
			InterpolateMatrix_AI(v11, fp);
		}
		//loc_81DDC
		s4--;
		s5 += 4;
		s7 += 4;
	} while (s4 != 0);
	//j       loc_81714
	///@TODO
	assert(FALSE);//Unimplemented jump
}

void CalcAnimatingItem_ASM(struct ITEM_INFO* item /*s3*/, struct object_info* object /*s6*/, int* fp)//81504(<), 83548
{
	int frames;//$s0
	short* s2;
	int s4;
	int at = 0;
	int v0 = 0;
	int* a2 = NULL;
	int v1 = 0;
	short* s7 = NULL;
	short* v00 = NULL;
	int a0 = 0;
	long* s5 = NULL;

	//v0 = 0x1FF0000
	//v1 = 0xEF0000
	fp[36] = 0x1FF0000;
	fp[37] = 0xEF0000;

	frames = GetFrames_AI(item, fp);
	mmPushMatrix_AI(fp);
	mTranslateAbsXYZ_AI(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, fp);
	mRotYXZ_AI(item->pos.y_rot, item->pos.x_rot, item->pos.z_rot, fp);

	//a0 = object->object_mip
	//v0 = object[1].loaded
	if (object->object_mip != 0 && object[1].loaded && object->object_mip < TRZ && fp[46] == 0)
	{
		object++;
	}

	//loc_81584
	calc_animating_item_clip_window(item, (unsigned short*)fp[30], fp);

	at = 0;
	v0 = mClipBoundingBox_AI((unsigned short*)fp[30], fp);

	if (v0 != 0)
	{
		fp[19] = 0;
		a2 = (int*)fp[16];
		v1 = fp[30];
		((short*)a2)[0] = v0;
		a2[1] = (int)item;
		a2[2] = v1;
		s2 = (short*)item->data;
		//s1 = 1
		//v0 = object->mesh_index
		s7 = (short*)(fp[40] + (object->mesh_index << 2));
		//v0 = object->bone_index
		s5 = (long*)(fp[41] + (object->bone_index << 2));

		if (frames != 0)
		{
			erk_interpolated(item, object, frames, s2, s5, s7, fp);//loc_81C60
			assert(FALSE);///@todo check return?
		}

		v00 = (short*)fp[30];
		mTranslateXYZ_AI(v00[6], v00[7], v00[8], fp);
		//v0 = fp[30];
		//gp = item->meshswap_meshbits
		//s3 = item->mesh_bits
		fp[32] = fp[30] + 0x12;
		mRotSuperPackedYXZ_AI(fp);

		if ((item->mesh_bits & 1))
		{
			a0 = ((int*)s7)[0];
			if ((item->meshswap_meshbits & 1))
			{
				a0 = ((int*)s7)[1];
			}

			//loc_81628
			stash_the_info(a0, fp);
		}
		//loc_81630
		s7 += 4;
		s4 = object->nmeshes - 1;
		if (s4 <= 0)
		{
			//loc_81714
			if (fp[19] > 0)
			{
				fp[18]++;
				((short*)fp[16])[1] = fp[19];
				fp[16] += 12;
			}
			mmPopMatrix_AI(fp);
			return;
		}

		//loc_81644
		do
		{
			if ((s5[0] & 0x1))
			{
				mmPopMatrix_AI(fp);
			}

			if ((s5[0] & 0x2))
			{
				mmPushMatrix_AI(fp);
			}

			mTranslateXYZ_AI(s5[1], s5[2], s5[3], fp);
			mRotSuperPackedYXZ_AI(fp);

			if ((item->data != NULL) && (s5[0] & 0x1C))
			{
				if ((s5[0] & 0x8))
				{
					mRotY_AI(*s2++, fp);
				}
				//loc_816B4
				if ((s5[0] & 0x4))
				{
					mRotX_AI(*s2++, fp);
				}
				//loc_816CC
				if ((s5[0] & 0x10))
				{
					mRotZ_AI(*s2++, fp);
				}
			}
			//loc_816E0
			//s1 = 1 << 1

			if ((1 << 1) & item->mesh_bits)
			{
				if (item->meshswap_meshbits & (1 << 1))
				{
					a0 = ((int*)s7)[1];
					stash_the_info(a0, fp);
				}
				else
				{
					a0 = ((int*)s7)[0];
					stash_the_info(a0, fp);
				}
				//loc_816FC
			}
			//loc_81704
			s4--;
			s7 += 4;
			s5 += 4;
		} while (s4 != 0);

		//loc_81714
		if (fp[19] > 0)
		{
			fp[18]++;
			((short*)fp[16])[1] = fp[19];
			fp[16] += 12;
		}
	}
	//loc_81738
	mmPopMatrix_AI(fp);
}

void stash_the_info(int meshp/*a0*/, int* fp)//81750
{
	int* at;

	at = (int*)fp[17];

	at[0] = meshp;

	at[1] = (R11 & 0xFFFF) | ((R12 & 0xFFFF) << 16);
	at[2] = (R13 & 0xFFFF) | ((R21 & 0xFFFF) << 16);
	at[3] = (R22 & 0xFFFF) | ((R23 & 0xFFFF) << 16);
	at[4] = (R31 & 0xFFFF) | ((R32 & 0xFFFF) << 16);

	at[5] = (R33 & 0xFFFF);
	at[6] = TRX;
	at[7] = TRY;
	at[8] = TRZ;

	at += 9;

	fp[19]++;
	fp[17] = (int)at;
}

void init_scratchpad(int* fp)//8281C(<) (F)
{
	int t0;
	int t1;
	int t2;
	int t3;
	int t4;
	int t5;
	int t6;
	int t7;
	int* at = &fp[47];
	fp[20] = (int)at;

	t0 = (R11 & 0xFFFF) | ((R12 & 0xFFFF) << 16);
	t1 = (R13 & 0xFFFF) | ((R21 & 0xFFFF) << 16);
	t2 = (R22 & 0xFFFF) | ((R23 & 0xFFFF) << 16);
	t3 = (R31 & 0xFFFF) | ((R32 & 0xFFFF) << 16);
	t4 = R33;
	t5 = TRX;
	t6 = TRY;
	t7 = TRZ;

	at[0] = t0;
	at[1] = t1;
	at[2] = t2;
	at[3] = t3;
	at[4] = t4;
	at[5] = t5;
	at[6] = t6;
	at[7] = t7;

	fp[16] = (int)&stashed_objects_list[0];
	fp[17] = (int)&stashed_matrix_list[0];
	fp[18] = 0;
	fp[24] = (int)&items[0];
	fp[38] = (int)&room[0];

	((short*)fp)[53] = camera.pos.room_number;
	fp[39] = (int)anims;
	fp[40] = (int)meshes;
	fp[41] = (int)bones;

	t0 = ((int*)MatrixStack)[5];
	t1 = ((int*)MatrixStack)[6];
	t2 = ((int*)MatrixStack)[7];

	fp[46] = BinocularRange;
	fp[27] = t0;
	fp[28] = t1;
	fp[29] = t2;

	/* Must be set in outer function */
	//s1 = number_draw_rooms 
	//s0 = &draw_rooms[0];
}


void CalcAllAnimatingItems_ASM()//82640, 84684
{
	int scratchPad[256];
	int* fp;
	int v1;
	struct room_info* r;//$s2
	struct static_info* s5;
	int at;
	int* a2;
	int v0;
	int i;//$s1
	int j;//$s3
	struct ITEM_INFO* item;//$s3
	struct object_info* object;//$s6
	int item_number;//$s2

	S_MemSet((char*)&scratchPad[0], 0, 1024);

	fp = &scratchPad[0];
	init_scratchpad(fp);

	if (number_draw_rooms > 0)
	{
		//loc_82658
		for (i = 0; i < number_draw_rooms; i++)
		{
			r = &room[draw_rooms[i]];
			((short*)fp)[52] = draw_rooms[i];
			((int*)fp)[25] = (int)r;
			mmPushMatrix_AI(fp);

			if (r->num_meshes > 0)
			{
				fp[36] = ((int*)&r->left)[0];
				fp[37] = ((int*)&r->top)[0];

				//loc_82698
				for (j = 0; j < r->num_meshes; j++)
				{
					s5 = &static_objects[r->mesh[j].static_number];

					if ((r->mesh[j].Flags & 1))
					{
						mmPushMatrix_AI(fp);
						mTranslateAbsXYZ_AI(r->mesh[j].x, r->mesh[j].y, r->mesh[j].z, fp);
						mRotY_AI(r->mesh[j].y_rot, fp);
						v1 = ((s5->flags) >> 2) << 10;
						at = TRZ;

						if (v1 && v1 < TRZ)
						{
							s5++;
						}//loc_82704

						v0 = mClipBoundingBox_AI((unsigned short*)&s5->x_minp, fp);

						if (v0)
						{
							a2 = (int*)fp[16];
							fp[18]++;
							((short*)a2)[0] = v0;
							((int*)a2)[1] = (int)&r->mesh[j];
							((short*)a2)[1] = 0;
							a2 += 3;
							fp[16] = (int)a2;
							v1 = s5->mesh_number;
							v0 = fp[40];

							stash_the_info(((int*)v0)[s5->mesh_number], fp);//((int*)meshes[s5->mesh_number])[0]
						}
						//loc_8274C
						mmPopMatrix_AI(fp);
					}//loc_82750
				}//loc_82750
			}
			//loc_8275C
			//s2 = r->item_number

			//v0 = r->item_number << 7
			if (r->item_number != -1)
			{
				item_number = r->item_number;

				//loc_8276C
				do
				{
					item = &((struct ITEM_INFO*)fp[24])[item_number];//&items[r->item_number]
					//v1 = r->item_number << 4	
					//v1 = item->object_number
					//s6 = objects
					object = &objects[item->object_number];

					//v0 = object->using_drawanimating_item
					//a1 = item->status

					if (object->using_drawanimating_item && item->status != 3)
					{
						//s2 = item
						CalcAnimatingItem_ASM(item, object, fp);

#if 0//Disabled, maybe not needed
						lw      $s2, arg_B0($fp)
						lw      $ra, arg_B4($fp)
						lw      $s1, arg_AC($fp)
						jr      $ra
						lw      $s0, arg_A8($fp)
#endif
						//item = s2 //Maybe restore backup check if modified in func above
					}
					//loc_827BC
					item_number = item->next_item;
				} while (item->next_item != -1);

			}//loc_827CC
			mmPopMatrix_AI(fp);
		}
	}//loc_827DC
#if !JULY_VERSION
	DrawAllAnimatingItems_ASM(fp[18]);
#endif
}


void DrawAllAnimatingItems_ASM(int s4)//82900(<)
{
	struct ITEM_INFO* item;//$a3
	struct STASHEDOBJ* sobject;//$s0
	struct STASHEDDAT* sdat;//$s2
	int i;//$s4
	int j;//$s1
	int s6;

	if (s4 > 0)
	{
		sobject = &stashed_objects_list[0];
		mPushMatrix();
		sdat = &stashed_matrix_list[0];

		//loc_8291C
		for(i = 0; i < s4; i++, sobject++)
		{
			s6 = 0x80;
			item = stashed_objects_list[i].item;

			if (sobject->numnodestodraw == 0)
			{	
				j = 1;
				S_CalculateStaticMeshLight(item->floor, item->touch_bits, item->mesh_bits, item->current_anim_state);
			}
			else
			{
				//loc_82950
				j = sobject->numnodestodraw;
				s6 =  0x80 - item->after_death;
				CalculateObjectLighting(item, sobject->frmptr0, sobject, sobject->numnodestodraw);
			}

			//loc_82964
			do
			{
				R11 = ((int*)&sdat->matrix[0])[0] & 0xFFFF;
				R12 = (((int*)&sdat->matrix[0])[0] >> 16) & 0xFFFF;
				R13 = ((int*)&sdat->matrix[0])[1] & 0xFFFF;
				R21 = (((int*)&sdat->matrix[0])[1] >> 16) & 0xFFFF;
				R22 = ((int*)&sdat->matrix[0])[2] & 0xFFFF;
				R23 = (((int*)&sdat->matrix[0])[2] >> 16) & 0xFFFF;
				R31 = ((int*)&sdat->matrix[0])[3] & 0xFFFF;
				R32 = (((int*)&sdat->matrix[0])[3] >> 16) & 0xFFFF;
				R33 = ((int*)&sdat->matrix[0])[4] & 0xFFFF;
				TRX = ((int*)&sdat->matrix[0])[5];
				TRY = ((int*)&sdat->matrix[0])[6];
				TRZ = ((int*)&sdat->matrix[0])[7];

				if (s6 != 0x80)
				{
					//loc_829C4
					if (s6 >= 5)
					{
						phd_PutPolygons_seethrough(sdat->mesh, s6);
					}
				}//loc_829C4
				else
				{
					phd_PutPolygons(sdat->mesh, sobject->clip);
				}
				sdat++;
			} while (--j > 0);
		} 
		//loc_829E8
		mPopMatrix();
	}
	//loc_829E8
	phd_left = 0;
	phd_right = 0x1FF;
	phd_top = 0;
	phd_bottom = 0xEF;
}