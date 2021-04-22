#include <gl.h>

Matrix sl_trans_mat, sl_rot_mat, sl_scale_mat;

static Matrix idmat = { 1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0 };

sl_do_rot_w(angle,axis)
float angle;
char axis;
{
 pushmatrix();
 loadmatrix(idmat);
 rot(angle,axis);
 multmatrix(sl_rot_mat);
 getmatrix(sl_rot_mat);
 popmatrix();
}

sl_do_rot(angle,axis)
float angle;
char axis;
{
 pushmatrix();
 loadmatrix(sl_rot_mat);
 rot(angle,axis);
 getmatrix(sl_rot_mat);
 popmatrix();
}

sl_do_translate_w(x,y,z)
float x,y,z;
{
 pushmatrix();
 loadmatrix(idmat);
 translate(x,y,z);
 multmatrix(sl_trans_mat);
 getmatrix(sl_trans_mat);
 popmatrix();
}

sl_do_translate(x,y,z)
float x,y,z;
{
 pushmatrix();
 loadmatrix(sl_trans_mat);
 translate(x,y,z);
 getmatrix(sl_trans_mat);
 popmatrix();
}

sl_do_scale(s)
float s;
{
 pushmatrix();
 loadmatrix(sl_scale_mat);
 scale(s,s,s);
 getmatrix(sl_scale_mat);
 popmatrix();
}

sl_init_transform()
{
 pushmatrix();
 loadmatrix(idmat);
 getmatrix(sl_scale_mat);
 getmatrix(sl_rot_mat);
 getmatrix(sl_trans_mat);
 popmatrix();
}
