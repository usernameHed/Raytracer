/*
** lum.c for  in /home/belfio_u/rendu/MUL/MUL_2014_rtracer/src
** 
** Made by ugo belfiore
** Login   <belfio_u@epitech.net>
** 
** Started on  Mon May 18 14:04:11 2015 ugo belfiore
** Last update Fri Jun  5 17:21:09 2015 ugo belfiore
*/

#include "mini.h"

static void	calculate_n_obj(t_st *s)
{
  if (s->x.t == CYLINDER)
    {
      rotate(&s->x.o.rot, &s->n, NULL, 2);
      s->n.vx = s->x.c.p.x - s->x.o.p.x;
      s->n.vy = s->x.c.p.y - s->x.o.p.y;
      s->n.vz = 0;
      rotate_inv(&s->x.o.rot, &s->n, NULL, 2);
    }
  if (s->x.t == CONE)
    {
      rotate(&s->x.o.rot, &s->n, NULL, 2);
      s->n.vx = s->x.c.p.x - s->x.o.p.x;
      s->n.vy = s->x.c.p.y - s->x.o.p.y;
      s->n.vz = 0 - (s->x.c.p.z - s->x.o.p.z);
      rotate_inv(&s->x.o.rot, &s->n, NULL, 2);
    }
}

void	calculate_n(t_st *s)
{
  if (s->x.t == SPHERE)
    {
      rotate(&s->x.o.rot, &s->n, NULL, 2);
      s->n.vx = s->x.c.p.x - s->x.o.p.x;
      s->n.vy = s->x.c.p.y - s->x.o.p.y;
      s->n.vz = s->x.c.p.z - s->x.o.p.z;
      rotate_inv(&s->x.o.rot, &s->n, NULL, 2);
    }
  if (s->x.t == PLANE)
    {
      s->n.vx = 0;
      s->n.vy = 0;
      s->n.vz = 100;
    }
  calculate_n_obj(s);
}

void            light(t_st *s, t_cam *l)
{
  double        cosin;

  l->type = 0;
  s->x.c.v.vx = l->p.x - s->x.c.p.x;
  s->x.c.v.vy = l->p.y - s->x.c.p.y;
  s->x.c.v.vz = l->p.z - s->x.c.p.z;
  cosin = (((s->n.vx * s->x.c.v.vx) + (s->n.vy * s->x.c.v.vy)
            + (s->n.vz * s->x.c.v.vz))
           / sqrt((pow(s->n.vx, 2) + pow(s->n.vy, 2) + pow(s->n.vz, 2)) *
                  (pow(s->x.c.v.vx, 2) + pow(s->x.c.v.vy, 2)
                   + pow(s->x.c.v.vz, 2))));
  if (cosin > 0.000001)
    {
      if (shadow(s) == -1)
      	return ;
      my_change_color(s, cosin, l);
    }
}
