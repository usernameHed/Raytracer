/*
** obj.c for rtv1 in /home/toozs-_c/Prog_tests/rtv1/sources
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Thu Mar  5 10:17:14 2015 cristopher toozs-hobson
** Last update Fri Jun  5 16:10:47 2015 ugo belfiore
*/

#include "mini.h"

void		delta(t_x *x, double a, double b, double ca)
{
  double	delta;

  delta = pow(b, 2) - (4 * a * ca);
  if (delta >= 0)
    {
      x->x1 = ((-b) + sqrt(delta)) / (2 * a);
      x->x2 = ((-b) - sqrt(delta)) / (2 * a);
    }
}

void		inter_sphere(t_cam *c, t_sph *s)
{
  double	a;
  double	b;
  double	ca;

  s->x.x1 = 10000000;
  s->x.x2 = 10000000;
  s->x.t = SPHERE;
  translation(&c->p, s->p.x, s->p.y, s->p.z);
  rotate(&s->rot, &c->v, &c->p, 3);
  a = pow(c->v.vx, 2) + pow(c->v.vy, 2) + pow(c->v.vz, 2);
  b = 2 * ((c->p.x * c->v.vx) + (c->p.y * c->v.vy) + (c->p.z * c->v.vz));
  ca = pow(c->p.x, 2) + pow(c->p.y, 2) + pow(c->p.z, 2) - pow(s->r, 2);
  rotate_inv(&s->rot, &c->v, &c->p, 3);
  inverse_translation(&c->p, s->p.x, s->p.y, s->p.z);
  s->x.p.x = s->p.x;
  s->x.p.y = s->p.y;
  s->x.p.z = s->p.z;
  s->x.rot.x = s->rot.x;
  s->x.rot.y = s->rot.y;
  s->x.rot.z = s->rot.z;
  delta(&s->x, a, b, ca);
}

void		inter_cone(t_cam *c, t_cone *co)
{
  double	tmp_angle;
  double	a;
  double	b;
  double	ca;

  co->x.x1 = 10000000;
  co->x.x2 = 10000000;
  co->x.t = CONE;
  tmp_angle = (co->r * M_PI) / 180;
  translation(&c->p, co->p.x, co->p.y, co->p.z);
  rotate(&co->rot, &c->v, &c->p, 3);
  a = (c->v.vx * c->v.vx) + (c->v.vy * c->v.vy) - ((c->v.vz * c->v.vz) /
     (tan(tmp_angle) * tan(tmp_angle)));
  b = (2 * c->p.x * c->v.vx)
    + (2 * c->p.y * c->v.vy) - (2 * c->p.z * c->v.vz /
			      (tan(tmp_angle) * tan(tmp_angle)));
  ca = (c->p.x * c->p.x) + (c->p.y * c->p.y)
    - ((c->p.z * c->p.z)
       / (tan(tmp_angle) * tan(tmp_angle)));
  rotate_inv(&co->rot, &c->v, &c->p, 3);
  inverse_translation(&c->p, co->p.x, co->p.y, co->p.z);
  co->x.p.x = co->p.x;
  co->x.p.y = co->p.y;
  co->x.p.z = co->p.z;
  delta(&co->x, a, b, ca);
}

void		inter_cyl(t_cam *c, t_cyl *cy)
{
  double	a;
  double	b;
  double	ca;

  cy->x.x1 = 10000000;
  cy->x.x2 = 10000000;
  cy->x.t = CYLINDER;
  translation(&c->p, cy->p.x, cy->p.y, cy->p.z);
  rotate(&cy->rot, &c->v, &c->p, 3);
  a = pow(c->v.vx, 2) + pow(c->v.vy, 2);
  b = (2 * c->p.x * c->v.vx)
    + (2 * c->p.y * c->v.vy);
  ca = pow(c->p.x, 2)
    + pow(c->p.y, 2) - pow(cy->r, 2);
  rotate_inv(&cy->rot, &c->v, &c->p, 3);
  inverse_translation(&c->p, cy->p.x, cy->p.y, cy->p.z);
  cy->x.p.x = cy->p.x;
  cy->x.p.y = cy->p.y;
  cy->x.p.z = cy->p.z;
  delta(&cy->x, a, b, ca);
}

void		inter_plan(t_cam *c, t_plan *pl)
{
  rotate(&pl->rot, &c->v, &c->p, 3);
  if (c->v.vz != 0)
    pl->k = -((c->p.z + pl->z) / c->v.vz);
  rotate_inv(&pl->rot, &c->v, &c->p, 3);
}
