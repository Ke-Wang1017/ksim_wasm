#include <chrono>
#include <cstdio>
#include <cstring>
#include <string>
#include <thread>
#include <vector>

#include "mujoco/mujoco.h"

#include <emscripten/fetch.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>
#include <vector>

using namespace emscripten;

int finish(const char *msg = NULL, mjModel *m = NULL) {
  if (m  ) { mj_deleteModel(m); }
  if (msg) { std::printf("%s\n", msg); }
  return 0;
}

class Model {
public:
  Model() { m = NULL; }

  static Model load_from_xml(const std::string filename) {
    Model model;
    char error[1000] = "Could not load xml model";
    model.m = mj_loadXML(filename.c_str(), 0, error, 1000);
    if (!model.m) { finish(error, model.m); }
    return model;
  }

  mjModel *ptr     () { return m; }
  mjModel getVal   () { return *m; }

  // MJMODEL_DEFINITIONS
  int nq            () { return m->nq            ; }
  int nv            () { return m->nv            ; }
  int nu            () { return m->nu            ; }
  int na            () { return m->na            ; }
  int nbody         () { return m->nbody         ; }
  int njnt          () { return m->njnt          ; }
  int ngeom         () { return m->ngeom         ; }
  int nsite         () { return m->nsite         ; }
  int ncam          () { return m->ncam          ; }
  int nlight        () { return m->nlight        ; }
  int nmesh         () { return m->nmesh         ; }
  int nmeshvert     () { return m->nmeshvert     ; }
  int nmeshtexvert  () { return m->nmeshtexvert  ; }
  int nmeshface     () { return m->nmeshface     ; }
  int nmeshgraph    () { return m->nmeshgraph    ; }
  int nskin         () { return m->nskin         ; }
  int nskinvert     () { return m->nskinvert     ; }
  int nskintexvert  () { return m->nskintexvert  ; }
  int nskinface     () { return m->nskinface     ; }
  int nskinbone     () { return m->nskinbone     ; }
  int nskinbonevert () { return m->nskinbonevert ; }
  int nhfield       () { return m->nhfield       ; }
  int nhfielddata   () { return m->nhfielddata   ; }
  int ntex          () { return m->ntex          ; }
  int ntexdata      () { return m->ntexdata      ; }
  int nmat          () { return m->nmat          ; }
  int npair         () { return m->npair         ; }
  int nexclude      () { return m->nexclude      ; }
  int neq           () { return m->neq           ; }
  int ntendon       () { return m->ntendon       ; }
  int nwrap         () { return m->nwrap         ; }
  int nsensor       () { return m->nsensor       ; }
  int nnumeric      () { return m->nnumeric      ; }
  int nnumericdata  () { return m->nnumericdata  ; }
  int ntext         () { return m->ntext         ; }
  int ntextdata     () { return m->ntextdata     ; }
  int ntuple        () { return m->ntuple        ; }
  int ntupledata    () { return m->ntupledata    ; }
  int nkey          () { return m->nkey          ; }
  int nmocap        () { return m->nmocap        ; }
  int nplugin       () { return m->nplugin       ; }
  int npluginattr   () { return m->npluginattr   ; }
  int nuser_body    () { return m->nuser_body    ; }
  int nuser_jnt     () { return m->nuser_jnt     ; }
  int nuser_geom    () { return m->nuser_geom    ; }
  int nuser_site    () { return m->nuser_site    ; }
  int nuser_cam     () { return m->nuser_cam     ; }
  int nuser_tendon  () { return m->nuser_tendon  ; }
  int nuser_actuator() { return m->nuser_actuator; }
  int nuser_sensor  () { return m->nuser_sensor  ; }
  int nnames        () { return m->nnames        ; }
  int nM            () { return m->nM            ; }
  int nD            () { return m->nD            ; }
  int nemax         () { return m->nemax         ; }
  int njmax         () { return m->njmax         ; }
  int nconmax       () { return m->nconmax       ; }
  int nstack        () { return m->nstack        ; }
  int nuserdata     () { return m->nuserdata     ; }
  int nsensordata   () { return m->nsensordata   ; }
  int npluginstate  () { return m->npluginstate  ; }
  int nbuffer       () { return m->nbuffer       ; }
  val qpos0                 () { return val(typed_memory_view(m->nq              * 1        , m->qpos0                  )); }
  val qpos_spring           () { return val(typed_memory_view(m->nq              * 1        , m->qpos_spring            )); }
  val body_parentid         () { return val(typed_memory_view(m->nbody           * 1        , m->body_parentid          )); }
  val body_rootid           () { return val(typed_memory_view(m->nbody           * 1        , m->body_rootid            )); }
  val body_weldid           () { return val(typed_memory_view(m->nbody           * 1        , m->body_weldid            )); }
  val body_mocapid          () { return val(typed_memory_view(m->nbody           * 1        , m->body_mocapid           )); }
  val body_jntnum           () { return val(typed_memory_view(m->nbody           * 1        , m->body_jntnum            )); }
  val body_jntadr           () { return val(typed_memory_view(m->nbody           * 1        , m->body_jntadr            )); }
  val body_dofnum           () { return val(typed_memory_view(m->nbody           * 1        , m->body_dofnum            )); }
  val body_dofadr           () { return val(typed_memory_view(m->nbody           * 1        , m->body_dofadr            )); }
  val body_geomnum          () { return val(typed_memory_view(m->nbody           * 1        , m->body_geomnum           )); }
  val body_geomadr          () { return val(typed_memory_view(m->nbody           * 1        , m->body_geomadr           )); }
  val body_simple           () { return val(typed_memory_view(m->nbody           * 1        , m->body_simple            )); }
  val body_sameframe        () { return val(typed_memory_view(m->nbody           * 1        , m->body_sameframe         )); }
  val body_pos              () { return val(typed_memory_view(m->nbody           * 3        , m->body_pos               )); }
  val body_quat             () { return val(typed_memory_view(m->nbody           * 4        , m->body_quat              )); }
  val body_ipos             () { return val(typed_memory_view(m->nbody           * 3        , m->body_ipos              )); }
  val body_iquat            () { return val(typed_memory_view(m->nbody           * 4        , m->body_iquat             )); }
  val body_mass             () { return val(typed_memory_view(m->nbody           * 1        , m->body_mass              )); }
  val body_subtreemass      () { return val(typed_memory_view(m->nbody           * 1        , m->body_subtreemass       )); }
  val body_inertia          () { return val(typed_memory_view(m->nbody           * 3        , m->body_inertia           )); }
  val body_invweight0       () { return val(typed_memory_view(m->nbody           * 2        , m->body_invweight0        )); }
  val body_gravcomp         () { return val(typed_memory_view(m->nbody           * 1        , m->body_gravcomp          )); }
//val body_user             () { return val(typed_memory_view(m->nbody           * MJ_M(nuser_body, m->body_user              )); }
  val body_plugin           () { return val(typed_memory_view(m->nbody           * 1        , m->body_plugin            )); }
  val jnt_type              () { return val(typed_memory_view(m->njnt            * 1        , m->jnt_type               )); }
  val jnt_qposadr           () { return val(typed_memory_view(m->njnt            * 1        , m->jnt_qposadr            )); }
  val jnt_dofadr            () { return val(typed_memory_view(m->njnt            * 1        , m->jnt_dofadr             )); }
  val jnt_bodyid            () { return val(typed_memory_view(m->njnt            * 1        , m->jnt_bodyid             )); }
  val jnt_group             () { return val(typed_memory_view(m->njnt            * 1        , m->jnt_group              )); }
  val jnt_limited           () { return val(typed_memory_view(m->njnt            * 1        , m->jnt_limited            )); }
  val jnt_solref            () { return val(typed_memory_view(m->njnt            * mjNREF   , m->jnt_solref             )); }
  val jnt_solimp            () { return val(typed_memory_view(m->njnt            * mjNIMP   , m->jnt_solimp             )); }
  val jnt_pos               () { return val(typed_memory_view(m->njnt            * 3        , m->jnt_pos                )); }
  val jnt_axis              () { return val(typed_memory_view(m->njnt            * 3        , m->jnt_axis               )); }
  val jnt_stiffness         () { return val(typed_memory_view(m->njnt            * 1        , m->jnt_stiffness          )); }
  val jnt_range             () { return val(typed_memory_view(m->njnt            * 2        , m->jnt_range              )); }
  val jnt_margin            () { return val(typed_memory_view(m->njnt            * 1        , m->jnt_margin             )); }
//val jnt_user              () { return val(typed_memory_view(m->njnt            * MJ_M(nuser_jnt, m->jnt_user               )); }
  val dof_bodyid            () { return val(typed_memory_view(m->nv              * 1        , m->dof_bodyid             )); }
  val dof_jntid             () { return val(typed_memory_view(m->nv              * 1        , m->dof_jntid              )); }
  val dof_parentid          () { return val(typed_memory_view(m->nv              * 1        , m->dof_parentid           )); }
  val dof_Madr              () { return val(typed_memory_view(m->nv              * 1        , m->dof_Madr               )); }
  val dof_simplenum         () { return val(typed_memory_view(m->nv              * 1        , m->dof_simplenum          )); }
  val dof_solref            () { return val(typed_memory_view(m->nv              * mjNREF   , m->dof_solref             )); }
  val dof_solimp            () { return val(typed_memory_view(m->nv              * mjNIMP   , m->dof_solimp             )); }
  val dof_frictionloss      () { return val(typed_memory_view(m->nv              * 1        , m->dof_frictionloss       )); }
  val dof_armature          () { return val(typed_memory_view(m->nv              * 1        , m->dof_armature           )); }
  val dof_damping           () { return val(typed_memory_view(m->nv              * 1        , m->dof_damping            )); }
  val dof_invweight0        () { return val(typed_memory_view(m->nv              * 1        , m->dof_invweight0         )); }
  val dof_M0                () { return val(typed_memory_view(m->nv              * 1        , m->dof_M0                 )); }
  val geom_type             () { return val(typed_memory_view(m->ngeom           * 1        , m->geom_type              )); }
  val geom_contype          () { return val(typed_memory_view(m->ngeom           * 1        , m->geom_contype           )); }
  val geom_conaffinity      () { return val(typed_memory_view(m->ngeom           * 1        , m->geom_conaffinity       )); }
  val geom_condim           () { return val(typed_memory_view(m->ngeom           * 1        , m->geom_condim            )); }
  val geom_bodyid           () { return val(typed_memory_view(m->ngeom           * 1        , m->geom_bodyid            )); }
  val geom_dataid           () { return val(typed_memory_view(m->ngeom           * 1        , m->geom_dataid            )); }
  val geom_matid            () { return val(typed_memory_view(m->ngeom           * 1        , m->geom_matid             )); }
  val geom_group            () { return val(typed_memory_view(m->ngeom           * 1        , m->geom_group             )); }
  val geom_priority         () { return val(typed_memory_view(m->ngeom           * 1        , m->geom_priority          )); }
  val geom_sameframe        () { return val(typed_memory_view(m->ngeom           * 1        , m->geom_sameframe         )); }
  val geom_solmix           () { return val(typed_memory_view(m->ngeom           * 1        , m->geom_solmix            )); }
  val geom_solref           () { return val(typed_memory_view(m->ngeom           * mjNREF   , m->geom_solref            )); }
  val geom_solimp           () { return val(typed_memory_view(m->ngeom           * mjNIMP   , m->geom_solimp            )); }
  val geom_size             () { return val(typed_memory_view(m->ngeom           * 3        , m->geom_size              )); }
  val geom_rbound           () { return val(typed_memory_view(m->ngeom           * 1        , m->geom_rbound            )); }
  val geom_pos              () { return val(typed_memory_view(m->ngeom           * 3        , m->geom_pos               )); }
  val geom_quat             () { return val(typed_memory_view(m->ngeom           * 4        , m->geom_quat              )); }
  val geom_friction         () { return val(typed_memory_view(m->ngeom           * 3        , m->geom_friction          )); }
  val geom_margin           () { return val(typed_memory_view(m->ngeom           * 1        , m->geom_margin            )); }
  val geom_gap              () { return val(typed_memory_view(m->ngeom           * 1        , m->geom_gap               )); }
  val geom_fluid            () { return val(typed_memory_view(m->ngeom           * mjNFLUID , m->geom_fluid             )); }
//val geom_user             () { return val(typed_memory_view(m->ngeom           * MJ_M(nuser_geom, m->geom_user              )); }
  val geom_rgba             () { return val(typed_memory_view(m->ngeom           * 4        , m->geom_rgba              )); }
  val site_type             () { return val(typed_memory_view(m->nsite           * 1        , m->site_type              )); }
  val site_bodyid           () { return val(typed_memory_view(m->nsite           * 1        , m->site_bodyid            )); }
  val site_matid            () { return val(typed_memory_view(m->nsite           * 1        , m->site_matid             )); }
  val site_group            () { return val(typed_memory_view(m->nsite           * 1        , m->site_group             )); }
  val site_sameframe        () { return val(typed_memory_view(m->nsite           * 1        , m->site_sameframe         )); }
  val site_size             () { return val(typed_memory_view(m->nsite           * 3        , m->site_size              )); }
  val site_pos              () { return val(typed_memory_view(m->nsite           * 3        , m->site_pos               )); }
  val site_quat             () { return val(typed_memory_view(m->nsite           * 4        , m->site_quat              )); }
//val site_user             () { return val(typed_memory_view(m->nsite           * MJ_M(nuser_site, m->site_user              )); }
  val site_rgba             () { return val(typed_memory_view(m->nsite           * 4        , m->site_rgba              )); }
  val cam_mode              () { return val(typed_memory_view(m->ncam            * 1        , m->cam_mode               )); }
  val cam_bodyid            () { return val(typed_memory_view(m->ncam            * 1        , m->cam_bodyid             )); }
  val cam_targetbodyid      () { return val(typed_memory_view(m->ncam            * 1        , m->cam_targetbodyid       )); }
  val cam_pos               () { return val(typed_memory_view(m->ncam            * 3        , m->cam_pos                )); }
  val cam_quat              () { return val(typed_memory_view(m->ncam            * 4        , m->cam_quat               )); }
  val cam_poscom0           () { return val(typed_memory_view(m->ncam            * 3        , m->cam_poscom0            )); }
  val cam_pos0              () { return val(typed_memory_view(m->ncam            * 3        , m->cam_pos0               )); }
  val cam_mat0              () { return val(typed_memory_view(m->ncam            * 9        , m->cam_mat0               )); }
  val cam_fovy              () { return val(typed_memory_view(m->ncam            * 1        , m->cam_fovy               )); }
  val cam_ipd               () { return val(typed_memory_view(m->ncam            * 1        , m->cam_ipd                )); }
//val cam_user              () { return val(typed_memory_view(m->ncam            * MJ_M(nuser_cam, m->cam_user               )); }
  val light_mode            () { return val(typed_memory_view(m->nlight          * 1        , m->light_mode             )); }
  val light_bodyid          () { return val(typed_memory_view(m->nlight          * 1        , m->light_bodyid           )); }
  val light_targetbodyid    () { return val(typed_memory_view(m->nlight          * 1        , m->light_targetbodyid     )); }
  val light_directional     () { return val(typed_memory_view(m->nlight          * 1        , m->light_directional      )); }
  val light_castshadow      () { return val(typed_memory_view(m->nlight          * 1        , m->light_castshadow       )); }
  val light_active          () { return val(typed_memory_view(m->nlight          * 1        , m->light_active           )); }
  val light_pos             () { return val(typed_memory_view(m->nlight          * 3        , m->light_pos              )); }
  val light_dir             () { return val(typed_memory_view(m->nlight          * 3        , m->light_dir              )); }
  val light_poscom0         () { return val(typed_memory_view(m->nlight          * 3        , m->light_poscom0          )); }
  val light_pos0            () { return val(typed_memory_view(m->nlight          * 3        , m->light_pos0             )); }
  val light_dir0            () { return val(typed_memory_view(m->nlight          * 3        , m->light_dir0             )); }
  val light_attenuation     () { return val(typed_memory_view(m->nlight          * 3        , m->light_attenuation      )); }
  val light_cutoff          () { return val(typed_memory_view(m->nlight          * 1        , m->light_cutoff           )); }
  val light_exponent        () { return val(typed_memory_view(m->nlight          * 1        , m->light_exponent         )); }
  val light_ambient         () { return val(typed_memory_view(m->nlight          * 3        , m->light_ambient          )); }
  val light_diffuse         () { return val(typed_memory_view(m->nlight          * 3        , m->light_diffuse          )); }
  val light_specular        () { return val(typed_memory_view(m->nlight          * 3        , m->light_specular         )); }
  val mesh_vertadr          () { return val(typed_memory_view(m->nmesh           * 1        , m->mesh_vertadr           )); }
  val mesh_vertnum          () { return val(typed_memory_view(m->nmesh           * 1        , m->mesh_vertnum           )); }
  val mesh_texcoordadr      () { return val(typed_memory_view(m->nmesh           * 1        , m->mesh_texcoordadr       )); }
  val mesh_faceadr          () { return val(typed_memory_view(m->nmesh           * 1        , m->mesh_faceadr           )); }
  val mesh_facenum          () { return val(typed_memory_view(m->nmesh           * 1        , m->mesh_facenum           )); }
  val mesh_graphadr         () { return val(typed_memory_view(m->nmesh           * 1        , m->mesh_graphadr          )); }
  val mesh_vert             () { return val(typed_memory_view(m->nmeshvert       * 3        , m->mesh_vert              )); }
  val mesh_normal           () { return val(typed_memory_view(m->nmeshvert       * 3        , m->mesh_normal            )); }
  val mesh_texcoord         () { return val(typed_memory_view(m->nmeshtexvert    * 2        , m->mesh_texcoord          )); }
  val mesh_face             () { return val(typed_memory_view(m->nmeshface       * 3        , m->mesh_face              )); }
  val mesh_graph            () { return val(typed_memory_view(m->nmeshgraph      * 1        , m->mesh_graph             )); }
  val skin_matid            () { return val(typed_memory_view(m->nskin           * 1        , m->skin_matid             )); }
  val skin_group            () { return val(typed_memory_view(m->nskin           * 1        , m->skin_group             )); }
  val skin_rgba             () { return val(typed_memory_view(m->nskin           * 4        , m->skin_rgba              )); }
  val skin_inflate          () { return val(typed_memory_view(m->nskin           * 1        , m->skin_inflate           )); }
  val skin_vertadr          () { return val(typed_memory_view(m->nskin           * 1        , m->skin_vertadr           )); }
  val skin_vertnum          () { return val(typed_memory_view(m->nskin           * 1        , m->skin_vertnum           )); }
  val skin_texcoordadr      () { return val(typed_memory_view(m->nskin           * 1        , m->skin_texcoordadr       )); }
  val skin_faceadr          () { return val(typed_memory_view(m->nskin           * 1        , m->skin_faceadr           )); }
  val skin_facenum          () { return val(typed_memory_view(m->nskin           * 1        , m->skin_facenum           )); }
  val skin_boneadr          () { return val(typed_memory_view(m->nskin           * 1        , m->skin_boneadr           )); }
  val skin_bonenum          () { return val(typed_memory_view(m->nskin           * 1        , m->skin_bonenum           )); }
  val skin_vert             () { return val(typed_memory_view(m->nskinvert       * 3        , m->skin_vert              )); }
  val skin_texcoord         () { return val(typed_memory_view(m->nskintexvert    * 2        , m->skin_texcoord          )); }
  val skin_face             () { return val(typed_memory_view(m->nskinface       * 3        , m->skin_face              )); }
  val skin_bonevertadr      () { return val(typed_memory_view(m->nskinbone       * 1        , m->skin_bonevertadr       )); }
  val skin_bonevertnum      () { return val(typed_memory_view(m->nskinbone       * 1        , m->skin_bonevertnum       )); }
  val skin_bonebindpos      () { return val(typed_memory_view(m->nskinbone       * 3        , m->skin_bonebindpos       )); }
  val skin_bonebindquat     () { return val(typed_memory_view(m->nskinbone       * 4        , m->skin_bonebindquat      )); }
  val skin_bonebodyid       () { return val(typed_memory_view(m->nskinbone       * 1        , m->skin_bonebodyid        )); }
  val skin_bonevertid       () { return val(typed_memory_view(m->nskinbonevert   * 1        , m->skin_bonevertid        )); }
  val skin_bonevertweight   () { return val(typed_memory_view(m->nskinbonevert   * 1        , m->skin_bonevertweight    )); }
  val hfield_size           () { return val(typed_memory_view(m->nhfield         * 4        , m->hfield_size            )); }
  val hfield_nrow           () { return val(typed_memory_view(m->nhfield         * 1        , m->hfield_nrow            )); }
  val hfield_ncol           () { return val(typed_memory_view(m->nhfield         * 1        , m->hfield_ncol            )); }
  val hfield_adr            () { return val(typed_memory_view(m->nhfield         * 1        , m->hfield_adr             )); }
  val hfield_data           () { return val(typed_memory_view(m->nhfielddata     * 1        , m->hfield_data            )); }
  val tex_type              () { return val(typed_memory_view(m->ntex            * 1        , m->tex_type               )); }
  val tex_height            () { return val(typed_memory_view(m->ntex            * 1        , m->tex_height             )); }
  val tex_width             () { return val(typed_memory_view(m->ntex            * 1        , m->tex_width              )); }
  val tex_adr               () { return val(typed_memory_view(m->ntex            * 1        , m->tex_adr                )); }
  val tex_rgb               () { return val(typed_memory_view(m->ntexdata        * 1        , m->tex_rgb                )); }
  val mat_texid             () { return val(typed_memory_view(m->nmat            * 1        , m->mat_texid              )); }
  val mat_texuniform        () { return val(typed_memory_view(m->nmat            * 1        , m->mat_texuniform         )); }
  val mat_texrepeat         () { return val(typed_memory_view(m->nmat            * 2        , m->mat_texrepeat          )); }
  val mat_emission          () { return val(typed_memory_view(m->nmat            * 1        , m->mat_emission           )); }
  val mat_specular          () { return val(typed_memory_view(m->nmat            * 1        , m->mat_specular           )); }
  val mat_shininess         () { return val(typed_memory_view(m->nmat            * 1        , m->mat_shininess          )); }
  val mat_reflectance       () { return val(typed_memory_view(m->nmat            * 1        , m->mat_reflectance        )); }
  val mat_rgba              () { return val(typed_memory_view(m->nmat            * 4        , m->mat_rgba               )); }
  val pair_dim              () { return val(typed_memory_view(m->npair           * 1        , m->pair_dim               )); }
  val pair_geom1            () { return val(typed_memory_view(m->npair           * 1        , m->pair_geom1             )); }
  val pair_geom2            () { return val(typed_memory_view(m->npair           * 1        , m->pair_geom2             )); }
  val pair_signature        () { return val(typed_memory_view(m->npair           * 1        , m->pair_signature         )); }
  val pair_solref           () { return val(typed_memory_view(m->npair           * mjNREF   , m->pair_solref            )); }
  val pair_solimp           () { return val(typed_memory_view(m->npair           * mjNIMP   , m->pair_solimp            )); }
  val pair_margin           () { return val(typed_memory_view(m->npair           * 1        , m->pair_margin            )); }
  val pair_gap              () { return val(typed_memory_view(m->npair           * 1        , m->pair_gap               )); }
  val pair_friction         () { return val(typed_memory_view(m->npair           * 5        , m->pair_friction          )); }
  val exclude_signature     () { return val(typed_memory_view(m->nexclude        * 1        , m->exclude_signature      )); }
  val eq_type               () { return val(typed_memory_view(m->neq             * 1        , m->eq_type                )); }
  val eq_obj1id             () { return val(typed_memory_view(m->neq             * 1        , m->eq_obj1id              )); }
  val eq_obj2id             () { return val(typed_memory_view(m->neq             * 1        , m->eq_obj2id              )); }
  val eq_active             () { return val(typed_memory_view(m->neq             * 1        , m->eq_active              )); }
  val eq_solref             () { return val(typed_memory_view(m->neq             * mjNREF   , m->eq_solref              )); }
  val eq_solimp             () { return val(typed_memory_view(m->neq             * mjNIMP   , m->eq_solimp              )); }
  val eq_data               () { return val(typed_memory_view(m->neq             * mjNEQDATA, m->eq_data                )); }
  val tendon_adr            () { return val(typed_memory_view(m->ntendon         * 1        , m->tendon_adr             )); }
  val tendon_num            () { return val(typed_memory_view(m->ntendon         * 1        , m->tendon_num             )); }
  val tendon_matid          () { return val(typed_memory_view(m->ntendon         * 1        , m->tendon_matid           )); }
  val tendon_group          () { return val(typed_memory_view(m->ntendon         * 1        , m->tendon_group           )); }
  val tendon_limited        () { return val(typed_memory_view(m->ntendon         * 1        , m->tendon_limited         )); }
  val tendon_width          () { return val(typed_memory_view(m->ntendon         * 1        , m->tendon_width           )); }
  val tendon_solref_lim     () { return val(typed_memory_view(m->ntendon         * mjNREF   , m->tendon_solref_lim      )); }
  val tendon_solimp_lim     () { return val(typed_memory_view(m->ntendon         * mjNIMP   , m->tendon_solimp_lim      )); }
  val tendon_solref_fri     () { return val(typed_memory_view(m->ntendon         * mjNREF   , m->tendon_solref_fri      )); }
  val tendon_solimp_fri     () { return val(typed_memory_view(m->ntendon         * mjNIMP   , m->tendon_solimp_fri      )); }
  val tendon_range          () { return val(typed_memory_view(m->ntendon         * 2        , m->tendon_range           )); }
  val tendon_margin         () { return val(typed_memory_view(m->ntendon         * 1        , m->tendon_margin          )); }
  val tendon_stiffness      () { return val(typed_memory_view(m->ntendon         * 1        , m->tendon_stiffness       )); }
  val tendon_damping        () { return val(typed_memory_view(m->ntendon         * 1        , m->tendon_damping         )); }
  val tendon_frictionloss   () { return val(typed_memory_view(m->ntendon         * 1        , m->tendon_frictionloss    )); }
  val tendon_lengthspring   () { return val(typed_memory_view(m->ntendon         * 2        , m->tendon_lengthspring    )); }
  val tendon_length0        () { return val(typed_memory_view(m->ntendon         * 1        , m->tendon_length0         )); }
  val tendon_invweight0     () { return val(typed_memory_view(m->ntendon         * 1        , m->tendon_invweight0      )); }
//val tendon_user           () { return val(typed_memory_view(m->ntendon         * MJ_M(nuser_tendon, m->tendon_user            )); }
  val tendon_rgba           () { return val(typed_memory_view(m->ntendon         * 4        , m->tendon_rgba            )); }
  val wrap_type             () { return val(typed_memory_view(m->nwrap           * 1        , m->wrap_type              )); }
  val wrap_objid            () { return val(typed_memory_view(m->nwrap           * 1        , m->wrap_objid             )); }
  val wrap_prm              () { return val(typed_memory_view(m->nwrap           * 1        , m->wrap_prm               )); }
  val actuator_trntype      () { return val(typed_memory_view(m->nu              * 1        , m->actuator_trntype       )); }
  val actuator_dyntype      () { return val(typed_memory_view(m->nu              * 1        , m->actuator_dyntype       )); }
  val actuator_gaintype     () { return val(typed_memory_view(m->nu              * 1        , m->actuator_gaintype      )); }
  val actuator_biastype     () { return val(typed_memory_view(m->nu              * 1        , m->actuator_biastype      )); }
  val actuator_trnid        () { return val(typed_memory_view(m->nu              * 2        , m->actuator_trnid         )); }
  val actuator_actadr       () { return val(typed_memory_view(m->nu              * 1        , m->actuator_actadr        )); }
  val actuator_actnum       () { return val(typed_memory_view(m->nu              * 1        , m->actuator_actnum        )); }
  val actuator_group        () { return val(typed_memory_view(m->nu              * 1        , m->actuator_group         )); }
  val actuator_ctrllimited  () { return val(typed_memory_view(m->nu              * 1        , m->actuator_ctrllimited   )); }
  val actuator_forcelimited () { return val(typed_memory_view(m->nu              * 1        , m->actuator_forcelimited  )); }
  val actuator_actlimited   () { return val(typed_memory_view(m->nu              * 1        , m->actuator_actlimited    )); }
  val actuator_dynprm       () { return val(typed_memory_view(m->nu              * mjNDYN   , m->actuator_dynprm        )); }
  val actuator_gainprm      () { return val(typed_memory_view(m->nu              * mjNGAIN  , m->actuator_gainprm       )); }
  val actuator_biasprm      () { return val(typed_memory_view(m->nu              * mjNBIAS  , m->actuator_biasprm       )); }
  val actuator_ctrlrange    () { return val(typed_memory_view(m->nu              * 2        , m->actuator_ctrlrange     )); }
  val actuator_forcerange   () { return val(typed_memory_view(m->nu              * 2        , m->actuator_forcerange    )); }
  val actuator_actrange     () { return val(typed_memory_view(m->nu              * 2        , m->actuator_actrange      )); }
  val actuator_gear         () { return val(typed_memory_view(m->nu              * 6        , m->actuator_gear          )); }
  val actuator_cranklength  () { return val(typed_memory_view(m->nu              * 1        , m->actuator_cranklength   )); }
  val actuator_acc0         () { return val(typed_memory_view(m->nu              * 1        , m->actuator_acc0          )); }
  val actuator_length0      () { return val(typed_memory_view(m->nu              * 1        , m->actuator_length0       )); }
  val actuator_lengthrange  () { return val(typed_memory_view(m->nu              * 2        , m->actuator_lengthrange   )); }
//val actuator_user         () { return val(typed_memory_view(m->nu              * MJ_M(nuser_actuator, m->actuator_user          )); }
  val actuator_plugin       () { return val(typed_memory_view(m->nu              * 1        , m->actuator_plugin        )); }
  val sensor_type           () { return val(typed_memory_view(m->nsensor         * 1        , m->sensor_type            )); }
  val sensor_datatype       () { return val(typed_memory_view(m->nsensor         * 1        , m->sensor_datatype        )); }
  val sensor_needstage      () { return val(typed_memory_view(m->nsensor         * 1        , m->sensor_needstage       )); }
  val sensor_objtype        () { return val(typed_memory_view(m->nsensor         * 1        , m->sensor_objtype         )); }
  val sensor_objid          () { return val(typed_memory_view(m->nsensor         * 1        , m->sensor_objid           )); }
  val sensor_reftype        () { return val(typed_memory_view(m->nsensor         * 1        , m->sensor_reftype         )); }
  val sensor_refid          () { return val(typed_memory_view(m->nsensor         * 1        , m->sensor_refid           )); }
  val sensor_dim            () { return val(typed_memory_view(m->nsensor         * 1        , m->sensor_dim             )); }
  val sensor_adr            () { return val(typed_memory_view(m->nsensor         * 1        , m->sensor_adr             )); }
  val sensor_cutoff         () { return val(typed_memory_view(m->nsensor         * 1        , m->sensor_cutoff          )); }
  val sensor_noise          () { return val(typed_memory_view(m->nsensor         * 1        , m->sensor_noise           )); }
//val sensor_user           () { return val(typed_memory_view(m->nsensor         * MJ_M(nuser_sensor, m->sensor_user            )); }
  val sensor_plugin         () { return val(typed_memory_view(m->nsensor         * 1        , m->sensor_plugin          )); }
  val plugin                () { return val(typed_memory_view(m->nplugin         * 1        , m->plugin                 )); }
  val plugin_stateadr       () { return val(typed_memory_view(m->nplugin         * 1        , m->plugin_stateadr        )); }
  val plugin_statenum       () { return val(typed_memory_view(m->nplugin         * 1        , m->plugin_statenum        )); }
  val plugin_attr           () { return val(typed_memory_view(m->npluginattr     * 1        , m->plugin_attr            )); }
  val plugin_attradr        () { return val(typed_memory_view(m->nplugin         * 1        , m->plugin_attradr         )); }
  val numeric_adr           () { return val(typed_memory_view(m->nnumeric        * 1        , m->numeric_adr            )); }
  val numeric_size          () { return val(typed_memory_view(m->nnumeric        * 1        , m->numeric_size           )); }
  val numeric_data          () { return val(typed_memory_view(m->nnumericdata    * 1        , m->numeric_data           )); }
  val text_adr              () { return val(typed_memory_view(m->ntext           * 1        , m->text_adr               )); }
  val text_size             () { return val(typed_memory_view(m->ntext           * 1        , m->text_size              )); }
  val text_data             () { return val(typed_memory_view(m->ntextdata       * 1        , m->text_data              )); }
  val tuple_adr             () { return val(typed_memory_view(m->ntuple          * 1        , m->tuple_adr              )); }
  val tuple_size            () { return val(typed_memory_view(m->ntuple          * 1        , m->tuple_size             )); }
  val tuple_objtype         () { return val(typed_memory_view(m->ntupledata      * 1        , m->tuple_objtype          )); }
  val tuple_objid           () { return val(typed_memory_view(m->ntupledata      * 1        , m->tuple_objid            )); }
  val tuple_objprm          () { return val(typed_memory_view(m->ntupledata      * 1        , m->tuple_objprm           )); }
  val key_time              () { return val(typed_memory_view(m->nkey            * 1        , m->key_time               )); }
//val key_qpos              () { return val(typed_memory_view(m->nkey            * MJ_M(nq  , m->key_qpos               )); }
//val key_qvel              () { return val(typed_memory_view(m->nkey            * MJ_M(nv  , m->key_qvel               )); }
//val key_act               () { return val(typed_memory_view(m->nkey            * MJ_M(na  , m->key_act                )); }
//val key_mpos              () { return val(typed_memory_view(m->nkey            * MJ_M(nmocap, m->key_mpos               )); }
//val key_mquat             () { return val(typed_memory_view(m->nkey            * MJ_M(nmocap, m->key_mquat              )); }
//val key_ctrl              () { return val(typed_memory_view(m->nkey            * MJ_M(nu  , m->key_ctrl               )); }
  val name_bodyadr          () { return val(typed_memory_view(m->nbody           * 1        , m->name_bodyadr           )); }
  val name_jntadr           () { return val(typed_memory_view(m->njnt            * 1        , m->name_jntadr            )); }
  val name_geomadr          () { return val(typed_memory_view(m->ngeom           * 1        , m->name_geomadr           )); }
  val name_siteadr          () { return val(typed_memory_view(m->nsite           * 1        , m->name_siteadr           )); }
  val name_camadr           () { return val(typed_memory_view(m->ncam            * 1        , m->name_camadr            )); }
  val name_lightadr         () { return val(typed_memory_view(m->nlight          * 1        , m->name_lightadr          )); }
  val name_meshadr          () { return val(typed_memory_view(m->nmesh           * 1        , m->name_meshadr           )); }
  val name_skinadr          () { return val(typed_memory_view(m->nskin           * 1        , m->name_skinadr           )); }
  val name_hfieldadr        () { return val(typed_memory_view(m->nhfield         * 1        , m->name_hfieldadr         )); }
  val name_texadr           () { return val(typed_memory_view(m->ntex            * 1        , m->name_texadr            )); }
  val name_matadr           () { return val(typed_memory_view(m->nmat            * 1        , m->name_matadr            )); }
  val name_pairadr          () { return val(typed_memory_view(m->npair           * 1        , m->name_pairadr           )); }
  val name_excludeadr       () { return val(typed_memory_view(m->nexclude        * 1        , m->name_excludeadr        )); }
  val name_eqadr            () { return val(typed_memory_view(m->neq             * 1        , m->name_eqadr             )); }
  val name_tendonadr        () { return val(typed_memory_view(m->ntendon         * 1        , m->name_tendonadr         )); }
  val name_actuatoradr      () { return val(typed_memory_view(m->nu              * 1        , m->name_actuatoradr       )); }
  val name_sensoradr        () { return val(typed_memory_view(m->nsensor         * 1        , m->name_sensoradr         )); }
  val name_numericadr       () { return val(typed_memory_view(m->nnumeric        * 1        , m->name_numericadr        )); }
  val name_textadr          () { return val(typed_memory_view(m->ntext           * 1        , m->name_textadr           )); }
  val name_tupleadr         () { return val(typed_memory_view(m->ntuple          * 1        , m->name_tupleadr          )); }
  val name_keyadr           () { return val(typed_memory_view(m->nkey            * 1        , m->name_keyadr            )); }
  val name_pluginadr        () { return val(typed_memory_view(m->nplugin         * 1        , m->name_pluginadr         )); }
  val names                 () { return val(typed_memory_view(m->nnames          * 1        , m->names                  )); }


private:
  mjModel *m;
};

class State {
public:
  State(Model m)  { d = mj_makeData(m.ptr()); }
  mjData *ptr  () { return d; }
  mjData getVal() { return *d; }

private:
  mjData *d;
};

class Simulation {
public:
  Simulation(Model *m, State *s) {
    _model = m;
    _state = s;
  }

  State *state() { return _state; }
  Model *model() { return _model; }
  void    step() { mj_step(_model->ptr(), _state->ptr()); }

  val    xquat() { return val(typed_memory_view(_model->ptr()->nbody * 4, _state->ptr()->xquat)); }
  val    xpos () { return val(typed_memory_view(_model->ptr()->nbody * 3, _state->ptr()->xpos )); }

private:
  Model *_model;
  State *_state;
};

// main function
int main(int argc, char **argv) {
  std::printf("MuJoCo version: %d\n\n", mj_version());
  return 0;
}

EMSCRIPTEN_BINDINGS(mujoco_wasm) {
  class_<Model>("Model")
      .constructor<>()
      .class_function("load_from_xml", &Model::load_from_xml)
      .function("ptr", &Model::ptr, allow_raw_pointers())
      .function("getVal"          , &Model::getVal      )
      // MJMODEL_BINDINGS
      .function("nq"                    , &Model::nq                    )
      .function("nv"                    , &Model::nv                    )
      .function("nu"                    , &Model::nu                    )
      .function("na"                    , &Model::na                    )
      .function("nbody"                 , &Model::nbody                 )
      .function("njnt"                  , &Model::njnt                  )
      .function("ngeom"                 , &Model::ngeom                 )
      .function("nsite"                 , &Model::nsite                 )
      .function("ncam"                  , &Model::ncam                  )
      .function("nlight"                , &Model::nlight                )
      .function("nmesh"                 , &Model::nmesh                 )
      .function("nmeshvert"             , &Model::nmeshvert             )
      .function("nmeshtexvert"          , &Model::nmeshtexvert          )
      .function("nmeshface"             , &Model::nmeshface             )
      .function("nmeshgraph"            , &Model::nmeshgraph            )
      .function("nskin"                 , &Model::nskin                 )
      .function("nskinvert"             , &Model::nskinvert             )
      .function("nskintexvert"          , &Model::nskintexvert          )
      .function("nskinface"             , &Model::nskinface             )
      .function("nskinbone"             , &Model::nskinbone             )
      .function("nskinbonevert"         , &Model::nskinbonevert         )
      .function("nhfield"               , &Model::nhfield               )
      .function("nhfielddata"           , &Model::nhfielddata           )
      .function("ntex"                  , &Model::ntex                  )
      .function("ntexdata"              , &Model::ntexdata              )
      .function("nmat"                  , &Model::nmat                  )
      .function("npair"                 , &Model::npair                 )
      .function("nexclude"              , &Model::nexclude              )
      .function("neq"                   , &Model::neq                   )
      .function("ntendon"               , &Model::ntendon               )
      .function("nwrap"                 , &Model::nwrap                 )
      .function("nsensor"               , &Model::nsensor               )
      .function("nnumeric"              , &Model::nnumeric              )
      .function("nnumericdata"          , &Model::nnumericdata          )
      .function("ntext"                 , &Model::ntext                 )
      .function("ntextdata"             , &Model::ntextdata             )
      .function("ntuple"                , &Model::ntuple                )
      .function("ntupledata"            , &Model::ntupledata            )
      .function("nkey"                  , &Model::nkey                  )
      .function("nmocap"                , &Model::nmocap                )
      .function("nplugin"               , &Model::nplugin               )
      .function("npluginattr"           , &Model::npluginattr           )
      .function("nuser_body"            , &Model::nuser_body            )
      .function("nuser_jnt"             , &Model::nuser_jnt             )
      .function("nuser_geom"            , &Model::nuser_geom            )
      .function("nuser_site"            , &Model::nuser_site            )
      .function("nuser_cam"             , &Model::nuser_cam             )
      .function("nuser_tendon"          , &Model::nuser_tendon          )
      .function("nuser_actuator"        , &Model::nuser_actuator        )
      .function("nuser_sensor"          , &Model::nuser_sensor          )
      .function("nnames"                , &Model::nnames                )
      .function("nM"                    , &Model::nM                    )
      .function("nD"                    , &Model::nD                    )
      .function("nemax"                 , &Model::nemax                 )
      .function("njmax"                 , &Model::njmax                 )
      .function("nconmax"               , &Model::nconmax               )
      .function("nstack"                , &Model::nstack                )
      .function("nuserdata"             , &Model::nuserdata             )
      .function("nsensordata"           , &Model::nsensordata           )
      .function("npluginstate"          , &Model::npluginstate          )
      .function("nbuffer"               , &Model::nbuffer               )
      .function("qpos0"                 , &Model::qpos0                 )
      .function("qpos_spring"           , &Model::qpos_spring           )
      .function("body_parentid"         , &Model::body_parentid         )
      .function("body_rootid"           , &Model::body_rootid           )
      .function("body_weldid"           , &Model::body_weldid           )
      .function("body_mocapid"          , &Model::body_mocapid          )
      .function("body_jntnum"           , &Model::body_jntnum           )
      .function("body_jntadr"           , &Model::body_jntadr           )
      .function("body_dofnum"           , &Model::body_dofnum           )
      .function("body_dofadr"           , &Model::body_dofadr           )
      .function("body_geomnum"          , &Model::body_geomnum          )
      .function("body_geomadr"          , &Model::body_geomadr          )
      .function("body_simple"           , &Model::body_simple           )
      .function("body_sameframe"        , &Model::body_sameframe        )
      .function("body_pos"              , &Model::body_pos              )
      .function("body_quat"             , &Model::body_quat             )
      .function("body_ipos"             , &Model::body_ipos             )
      .function("body_iquat"            , &Model::body_iquat            )
      .function("body_mass"             , &Model::body_mass             )
      .function("body_subtreemass"      , &Model::body_subtreemass      )
      .function("body_inertia"          , &Model::body_inertia          )
      .function("body_invweight0"       , &Model::body_invweight0       )
      .function("body_gravcomp"         , &Model::body_gravcomp         )
    //.function("body_user"             , &Model::body_user             )
      .function("body_plugin"           , &Model::body_plugin           )
      .function("jnt_type"              , &Model::jnt_type              )
      .function("jnt_qposadr"           , &Model::jnt_qposadr           )
      .function("jnt_dofadr"            , &Model::jnt_dofadr            )
      .function("jnt_bodyid"            , &Model::jnt_bodyid            )
      .function("jnt_group"             , &Model::jnt_group             )
      .function("jnt_limited"           , &Model::jnt_limited           )
      .function("jnt_solref"            , &Model::jnt_solref            )
      .function("jnt_solimp"            , &Model::jnt_solimp            )
      .function("jnt_pos"               , &Model::jnt_pos               )
      .function("jnt_axis"              , &Model::jnt_axis              )
      .function("jnt_stiffness"         , &Model::jnt_stiffness         )
      .function("jnt_range"             , &Model::jnt_range             )
      .function("jnt_margin"            , &Model::jnt_margin            )
    //.function("jnt_user"              , &Model::jnt_user              )
      .function("dof_bodyid"            , &Model::dof_bodyid            )
      .function("dof_jntid"             , &Model::dof_jntid             )
      .function("dof_parentid"          , &Model::dof_parentid          )
      .function("dof_Madr"              , &Model::dof_Madr              )
      .function("dof_simplenum"         , &Model::dof_simplenum         )
      .function("dof_solref"            , &Model::dof_solref            )
      .function("dof_solimp"            , &Model::dof_solimp            )
      .function("dof_frictionloss"      , &Model::dof_frictionloss      )
      .function("dof_armature"          , &Model::dof_armature          )
      .function("dof_damping"           , &Model::dof_damping           )
      .function("dof_invweight0"        , &Model::dof_invweight0        )
      .function("dof_M0"                , &Model::dof_M0                )
      .function("geom_type"             , &Model::geom_type             )
      .function("geom_contype"          , &Model::geom_contype          )
      .function("geom_conaffinity"      , &Model::geom_conaffinity      )
      .function("geom_condim"           , &Model::geom_condim           )
      .function("geom_bodyid"           , &Model::geom_bodyid           )
      .function("geom_dataid"           , &Model::geom_dataid           )
      .function("geom_matid"            , &Model::geom_matid            )
      .function("geom_group"            , &Model::geom_group            )
      .function("geom_priority"         , &Model::geom_priority         )
      .function("geom_sameframe"        , &Model::geom_sameframe        )
      .function("geom_solmix"           , &Model::geom_solmix           )
      .function("geom_solref"           , &Model::geom_solref           )
      .function("geom_solimp"           , &Model::geom_solimp           )
      .function("geom_size"             , &Model::geom_size             )
      .function("geom_rbound"           , &Model::geom_rbound           )
      .function("geom_pos"              , &Model::geom_pos              )
      .function("geom_quat"             , &Model::geom_quat             )
      .function("geom_friction"         , &Model::geom_friction         )
      .function("geom_margin"           , &Model::geom_margin           )
      .function("geom_gap"              , &Model::geom_gap              )
      .function("geom_fluid"            , &Model::geom_fluid            )
    //.function("geom_user"             , &Model::geom_user             )
      .function("geom_rgba"             , &Model::geom_rgba             )
      .function("site_type"             , &Model::site_type             )
      .function("site_bodyid"           , &Model::site_bodyid           )
      .function("site_matid"            , &Model::site_matid            )
      .function("site_group"            , &Model::site_group            )
      .function("site_sameframe"        , &Model::site_sameframe        )
      .function("site_size"             , &Model::site_size             )
      .function("site_pos"              , &Model::site_pos              )
      .function("site_quat"             , &Model::site_quat             )
    //.function("site_user"             , &Model::site_user             )
      .function("site_rgba"             , &Model::site_rgba             )
      .function("cam_mode"              , &Model::cam_mode              )
      .function("cam_bodyid"            , &Model::cam_bodyid            )
      .function("cam_targetbodyid"      , &Model::cam_targetbodyid      )
      .function("cam_pos"               , &Model::cam_pos               )
      .function("cam_quat"              , &Model::cam_quat              )
      .function("cam_poscom0"           , &Model::cam_poscom0           )
      .function("cam_pos0"              , &Model::cam_pos0              )
      .function("cam_mat0"              , &Model::cam_mat0              )
      .function("cam_fovy"              , &Model::cam_fovy              )
      .function("cam_ipd"               , &Model::cam_ipd               )
    //.function("cam_user"              , &Model::cam_user              )
      .function("light_mode"            , &Model::light_mode            )
      .function("light_bodyid"          , &Model::light_bodyid          )
      .function("light_targetbodyid"    , &Model::light_targetbodyid    )
      .function("light_directional"     , &Model::light_directional     )
      .function("light_castshadow"      , &Model::light_castshadow      )
      .function("light_active"          , &Model::light_active          )
      .function("light_pos"             , &Model::light_pos             )
      .function("light_dir"             , &Model::light_dir             )
      .function("light_poscom0"         , &Model::light_poscom0         )
      .function("light_pos0"            , &Model::light_pos0            )
      .function("light_dir0"            , &Model::light_dir0            )
      .function("light_attenuation"     , &Model::light_attenuation     )
      .function("light_cutoff"          , &Model::light_cutoff          )
      .function("light_exponent"        , &Model::light_exponent        )
      .function("light_ambient"         , &Model::light_ambient         )
      .function("light_diffuse"         , &Model::light_diffuse         )
      .function("light_specular"        , &Model::light_specular        )
      .function("mesh_vertadr"          , &Model::mesh_vertadr          )
      .function("mesh_vertnum"          , &Model::mesh_vertnum          )
      .function("mesh_texcoordadr"      , &Model::mesh_texcoordadr      )
      .function("mesh_faceadr"          , &Model::mesh_faceadr          )
      .function("mesh_facenum"          , &Model::mesh_facenum          )
      .function("mesh_graphadr"         , &Model::mesh_graphadr         )
      .function("mesh_vert"             , &Model::mesh_vert             )
      .function("mesh_normal"           , &Model::mesh_normal           )
      .function("mesh_texcoord"         , &Model::mesh_texcoord         )
      .function("mesh_face"             , &Model::mesh_face             )
      .function("mesh_graph"            , &Model::mesh_graph            )
      .function("skin_matid"            , &Model::skin_matid            )
      .function("skin_group"            , &Model::skin_group            )
      .function("skin_rgba"             , &Model::skin_rgba             )
      .function("skin_inflate"          , &Model::skin_inflate          )
      .function("skin_vertadr"          , &Model::skin_vertadr          )
      .function("skin_vertnum"          , &Model::skin_vertnum          )
      .function("skin_texcoordadr"      , &Model::skin_texcoordadr      )
      .function("skin_faceadr"          , &Model::skin_faceadr          )
      .function("skin_facenum"          , &Model::skin_facenum          )
      .function("skin_boneadr"          , &Model::skin_boneadr          )
      .function("skin_bonenum"          , &Model::skin_bonenum          )
      .function("skin_vert"             , &Model::skin_vert             )
      .function("skin_texcoord"         , &Model::skin_texcoord         )
      .function("skin_face"             , &Model::skin_face             )
      .function("skin_bonevertadr"      , &Model::skin_bonevertadr      )
      .function("skin_bonevertnum"      , &Model::skin_bonevertnum      )
      .function("skin_bonebindpos"      , &Model::skin_bonebindpos      )
      .function("skin_bonebindquat"     , &Model::skin_bonebindquat     )
      .function("skin_bonebodyid"       , &Model::skin_bonebodyid       )
      .function("skin_bonevertid"       , &Model::skin_bonevertid       )
      .function("skin_bonevertweight"   , &Model::skin_bonevertweight   )
      .function("hfield_size"           , &Model::hfield_size           )
      .function("hfield_nrow"           , &Model::hfield_nrow           )
      .function("hfield_ncol"           , &Model::hfield_ncol           )
      .function("hfield_adr"            , &Model::hfield_adr            )
      .function("hfield_data"           , &Model::hfield_data           )
      .function("tex_type"              , &Model::tex_type              )
      .function("tex_height"            , &Model::tex_height            )
      .function("tex_width"             , &Model::tex_width             )
      .function("tex_adr"               , &Model::tex_adr               )
      .function("tex_rgb"               , &Model::tex_rgb               )
      .function("mat_texid"             , &Model::mat_texid             )
      .function("mat_texuniform"        , &Model::mat_texuniform        )
      .function("mat_texrepeat"         , &Model::mat_texrepeat         )
      .function("mat_emission"          , &Model::mat_emission          )
      .function("mat_specular"          , &Model::mat_specular          )
      .function("mat_shininess"         , &Model::mat_shininess         )
      .function("mat_reflectance"       , &Model::mat_reflectance       )
      .function("mat_rgba"              , &Model::mat_rgba              )
      .function("pair_dim"              , &Model::pair_dim              )
      .function("pair_geom1"            , &Model::pair_geom1            )
      .function("pair_geom2"            , &Model::pair_geom2            )
      .function("pair_signature"        , &Model::pair_signature        )
      .function("pair_solref"           , &Model::pair_solref           )
      .function("pair_solimp"           , &Model::pair_solimp           )
      .function("pair_margin"           , &Model::pair_margin           )
      .function("pair_gap"              , &Model::pair_gap              )
      .function("pair_friction"         , &Model::pair_friction         )
      .function("exclude_signature"     , &Model::exclude_signature     )
      .function("eq_type"               , &Model::eq_type               )
      .function("eq_obj1id"             , &Model::eq_obj1id             )
      .function("eq_obj2id"             , &Model::eq_obj2id             )
      .function("eq_active"             , &Model::eq_active             )
      .function("eq_solref"             , &Model::eq_solref             )
      .function("eq_solimp"             , &Model::eq_solimp             )
      .function("eq_data"               , &Model::eq_data               )
      .function("tendon_adr"            , &Model::tendon_adr            )
      .function("tendon_num"            , &Model::tendon_num            )
      .function("tendon_matid"          , &Model::tendon_matid          )
      .function("tendon_group"          , &Model::tendon_group          )
      .function("tendon_limited"        , &Model::tendon_limited        )
      .function("tendon_width"          , &Model::tendon_width          )
      .function("tendon_solref_lim"     , &Model::tendon_solref_lim     )
      .function("tendon_solimp_lim"     , &Model::tendon_solimp_lim     )
      .function("tendon_solref_fri"     , &Model::tendon_solref_fri     )
      .function("tendon_solimp_fri"     , &Model::tendon_solimp_fri     )
      .function("tendon_range"          , &Model::tendon_range          )
      .function("tendon_margin"         , &Model::tendon_margin         )
      .function("tendon_stiffness"      , &Model::tendon_stiffness      )
      .function("tendon_damping"        , &Model::tendon_damping        )
      .function("tendon_frictionloss"   , &Model::tendon_frictionloss   )
      .function("tendon_lengthspring"   , &Model::tendon_lengthspring   )
      .function("tendon_length0"        , &Model::tendon_length0        )
      .function("tendon_invweight0"     , &Model::tendon_invweight0     )
    //.function("tendon_user"           , &Model::tendon_user           )
      .function("tendon_rgba"           , &Model::tendon_rgba           )
      .function("wrap_type"             , &Model::wrap_type             )
      .function("wrap_objid"            , &Model::wrap_objid            )
      .function("wrap_prm"              , &Model::wrap_prm              )
      .function("actuator_trntype"      , &Model::actuator_trntype      )
      .function("actuator_dyntype"      , &Model::actuator_dyntype      )
      .function("actuator_gaintype"     , &Model::actuator_gaintype     )
      .function("actuator_biastype"     , &Model::actuator_biastype     )
      .function("actuator_trnid"        , &Model::actuator_trnid        )
      .function("actuator_actadr"       , &Model::actuator_actadr       )
      .function("actuator_actnum"       , &Model::actuator_actnum       )
      .function("actuator_group"        , &Model::actuator_group        )
      .function("actuator_ctrllimited"  , &Model::actuator_ctrllimited  )
      .function("actuator_forcelimited" , &Model::actuator_forcelimited )
      .function("actuator_actlimited"   , &Model::actuator_actlimited   )
      .function("actuator_dynprm"       , &Model::actuator_dynprm       )
      .function("actuator_gainprm"      , &Model::actuator_gainprm      )
      .function("actuator_biasprm"      , &Model::actuator_biasprm      )
      .function("actuator_ctrlrange"    , &Model::actuator_ctrlrange    )
      .function("actuator_forcerange"   , &Model::actuator_forcerange   )
      .function("actuator_actrange"     , &Model::actuator_actrange     )
      .function("actuator_gear"         , &Model::actuator_gear         )
      .function("actuator_cranklength"  , &Model::actuator_cranklength  )
      .function("actuator_acc0"         , &Model::actuator_acc0         )
      .function("actuator_length0"      , &Model::actuator_length0      )
      .function("actuator_lengthrange"  , &Model::actuator_lengthrange  )
    //.function("actuator_user"         , &Model::actuator_user         )
      .function("actuator_plugin"       , &Model::actuator_plugin       )
      .function("sensor_type"           , &Model::sensor_type           )
      .function("sensor_datatype"       , &Model::sensor_datatype       )
      .function("sensor_needstage"      , &Model::sensor_needstage      )
      .function("sensor_objtype"        , &Model::sensor_objtype        )
      .function("sensor_objid"          , &Model::sensor_objid          )
      .function("sensor_reftype"        , &Model::sensor_reftype        )
      .function("sensor_refid"          , &Model::sensor_refid          )
      .function("sensor_dim"            , &Model::sensor_dim            )
      .function("sensor_adr"            , &Model::sensor_adr            )
      .function("sensor_cutoff"         , &Model::sensor_cutoff         )
      .function("sensor_noise"          , &Model::sensor_noise          )
    //.function("sensor_user"           , &Model::sensor_user           )
      .function("sensor_plugin"         , &Model::sensor_plugin         )
      .function("plugin"                , &Model::plugin                )
      .function("plugin_stateadr"       , &Model::plugin_stateadr       )
      .function("plugin_statenum"       , &Model::plugin_statenum       )
      .function("plugin_attr"           , &Model::plugin_attr           )
      .function("plugin_attradr"        , &Model::plugin_attradr        )
      .function("numeric_adr"           , &Model::numeric_adr           )
      .function("numeric_size"          , &Model::numeric_size          )
      .function("numeric_data"          , &Model::numeric_data          )
      .function("text_adr"              , &Model::text_adr              )
      .function("text_size"             , &Model::text_size             )
      .function("text_data"             , &Model::text_data             )
      .function("tuple_adr"             , &Model::tuple_adr             )
      .function("tuple_size"            , &Model::tuple_size            )
      .function("tuple_objtype"         , &Model::tuple_objtype         )
      .function("tuple_objid"           , &Model::tuple_objid           )
      .function("tuple_objprm"          , &Model::tuple_objprm          )
      .function("key_time"              , &Model::key_time              )
    //.function("key_qpos"              , &Model::key_qpos              )
    //.function("key_qvel"              , &Model::key_qvel              )
    //.function("key_act"               , &Model::key_act               )
    //.function("key_mpos"              , &Model::key_mpos              )
    //.function("key_mquat"             , &Model::key_mquat             )
    //.function("key_ctrl"              , &Model::key_ctrl              )
      .function("name_bodyadr"          , &Model::name_bodyadr          )
      .function("name_jntadr"           , &Model::name_jntadr           )
      .function("name_geomadr"          , &Model::name_geomadr          )
      .function("name_siteadr"          , &Model::name_siteadr          )
      .function("name_camadr"           , &Model::name_camadr           )
      .function("name_lightadr"         , &Model::name_lightadr         )
      .function("name_meshadr"          , &Model::name_meshadr          )
      .function("name_skinadr"          , &Model::name_skinadr          )
      .function("name_hfieldadr"        , &Model::name_hfieldadr        )
      .function("name_texadr"           , &Model::name_texadr           )
      .function("name_matadr"           , &Model::name_matadr           )
      .function("name_pairadr"          , &Model::name_pairadr          )
      .function("name_excludeadr"       , &Model::name_excludeadr       )
      .function("name_eqadr"            , &Model::name_eqadr            )
      .function("name_tendonadr"        , &Model::name_tendonadr        )
      .function("name_actuatoradr"      , &Model::name_actuatoradr      )
      .function("name_sensoradr"        , &Model::name_sensoradr        )
      .function("name_numericadr"       , &Model::name_numericadr       )
      .function("name_textadr"          , &Model::name_textadr          )
      .function("name_tupleadr"         , &Model::name_tupleadr         )
      .function("name_keyadr"           , &Model::name_keyadr           )
      .function("name_pluginadr"        , &Model::name_pluginadr        )
      .function("names"                 , &Model::names                 )

;

  class_<State>("State")
      .constructor<Model>()
      .function("ptr"   , &State::ptr, allow_raw_pointers())
      .function("getVal", &State::getVal);

  class_<Simulation>("Simulation")
      .constructor<Model *, State *>()
      .function("step" , &Simulation::step)
      .function("state", &Simulation::state, allow_raw_pointers())
      .function("model", &Simulation::model, allow_raw_pointers())
      .function("xquat", &Simulation::xquat)
      .function("xpos" , &Simulation::xpos);

  //value_object<mjModel>("mjModel")
  //    .field("ngeom"      , &mjModel::ngeom)
  //    .field("nq"         , &mjModel::nq)
  //    .field("na"         , &mjModel::na)
  //    .field("nv"         , &mjModel::nv)
  //    .field("nu"         , &mjModel::nu)
  //    .field("nbody"      , &mjModel::nbody)
  //    .field("nsensordata", &mjModel::nsensordata)
  //    .field("nmesh"      , &mjModel::nmesh)
  //    .field("nmeshvert"  , &mjModel::nmeshvert)
  //    .field("nmeshface"  , &mjModel::nmeshface);
  //value_object<mjData>("mjData");
}