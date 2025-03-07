import * as THREE from 'three';
import { Reflector  } from './utils/Reflector.js';
import { MuJoCoDemo } from './main.js';

export async function reloadFunc() {
  // Delete the old scene and load the new scene
  this.scene.remove(this.scene.getObjectByName("MuJoCo Root"));
  [this.model, this.state, this.simulation, this.bodies, this.lights] =
    await loadSceneFromURL(this.mujoco, this.params.scene, this);
  this.simulation.forward();
  for (let i = 0; i < this.updateGUICallbacks.length; i++) {
    this.updateGUICallbacks[i](this.model, this.simulation, this.params);
  }
}

/** @param {MuJoCoDemo} parentContext*/
export function setupGUI(parentContext) {

  // Make sure we reset the camera when the scene is changed or reloaded.
  parentContext.updateGUICallbacks.length = 0;
  parentContext.updateGUICallbacks.push((model, simulation, params) => {
    // TODO: Use free camera parameters from MuJoCo
    parentContext.camera.position.set(2.0, 1.7, 1.7);
    parentContext.controls.target.set(0, 0.7, 0);
    parentContext.controls.update(); });

  // Add scene selection dropdown.
  let reload = reloadFunc.bind(parentContext);
  parentContext.gui.add(parentContext.params, 'scene', {
    "Humanoid": "humanoid.xml", "Cassie": "agility_cassie/scene.xml",
    "Hammock": "hammock.xml", "Balloons": "balloons.xml", "Hand": "shadow_hand/scene_right.xml",
    "Flag": "flag.xml", "Mug": "mug.xml", "Tendon": "model_with_tendon.xml", "Stompy_Solo_Arm": "stompy/_env_solo_arm.xml",
    "Stompy_dual_Arm": "stompy/_env_dual_arm.xml", "Stompy_torso": "stompy/_env_torso.xml",
  }).name('Example Scene').onChange(reload);

  // Add a help menu.
  // Parameters:
  //  Name: "Help".
  //  When pressed, a help menu is displayed in the top left corner. When pressed again
  //  the help menu is removed.
  //  Can also be triggered by pressing F1.
  // Has a dark transparent background.
  // Has two columns: one for putting the action description, and one for the action key trigger.keyframeNumber
  let keyInnerHTML = '';
  let actionInnerHTML = '';
  const displayHelpMenu = () => {
    if (parentContext.params.help) {
      const helpMenu = document.createElement('div');
      helpMenu.style.position = 'absolute';
      helpMenu.style.top = '10px';
      helpMenu.style.left = '10px';
      helpMenu.style.color = 'white';
      helpMenu.style.font = 'normal 18px Arial';
      helpMenu.style.backgroundColor = 'rgba(0, 0, 0, 0.5)';
      helpMenu.style.padding = '10px';
      helpMenu.style.borderRadius = '10px';
      helpMenu.style.display = 'flex';
      helpMenu.style.flexDirection = 'column';
      helpMenu.style.alignItems = 'center';
      helpMenu.style.justifyContent = 'center';
      helpMenu.style.width = '400px';
      helpMenu.style.height = '400px';
      helpMenu.style.overflow = 'auto';
      helpMenu.style.zIndex = '1000';

      const helpMenuTitle = document.createElement('div');
      helpMenuTitle.style.font = 'bold 24px Arial';
      helpMenuTitle.innerHTML = '';
      helpMenu.appendChild(helpMenuTitle);

      const helpMenuTable = document.createElement('table');
      helpMenuTable.style.width = '100%';
      helpMenuTable.style.marginTop = '10px';
      helpMenu.appendChild(helpMenuTable);

      const helpMenuTableBody = document.createElement('tbody');
      helpMenuTable.appendChild(helpMenuTableBody);

      const helpMenuRow = document.createElement('tr');
      helpMenuTableBody.appendChild(helpMenuRow);

      const helpMenuActionColumn = document.createElement('td');
      helpMenuActionColumn.style.width = '50%';
      helpMenuActionColumn.style.textAlign = 'right';
      helpMenuActionColumn.style.paddingRight = '10px';
      helpMenuRow.appendChild(helpMenuActionColumn);

      const helpMenuKeyColumn = document.createElement('td');
      helpMenuKeyColumn.style.width = '50%';
      helpMenuKeyColumn.style.textAlign = 'left';
      helpMenuKeyColumn.style.paddingLeft = '10px';
      helpMenuRow.appendChild(helpMenuKeyColumn);

      const helpMenuActionText = document.createElement('div');
      helpMenuActionText.innerHTML = actionInnerHTML;
      helpMenuActionColumn.appendChild(helpMenuActionText);

      const helpMenuKeyText = document.createElement('div');
      helpMenuKeyText.innerHTML = keyInnerHTML;
      helpMenuKeyColumn.appendChild(helpMenuKeyText);

      // Close buttom in the top.
      const helpMenuCloseButton = document.createElement('button');
      helpMenuCloseButton.innerHTML = 'Close';
      helpMenuCloseButton.style.position = 'absolute';
      helpMenuCloseButton.style.top = '10px';
      helpMenuCloseButton.style.right = '10px';
      helpMenuCloseButton.style.zIndex = '1001';
      helpMenuCloseButton.onclick = () => {
        helpMenu.remove();
      };
      helpMenu.appendChild(helpMenuCloseButton);

      document.body.appendChild(helpMenu);
    } else {
      document.body.removeChild(document.body.lastChild);
    }
  }
  document.addEventListener('keydown', (event) => {
    if (event.key === 'F1') {
      parentContext.params.help = !parentContext.params.help;
      displayHelpMenu();
      event.preventDefault();
    }
  });
  keyInnerHTML += 'F1<br>';
  actionInnerHTML += 'Help<br>';

  let simulationFolder = parentContext.gui.addFolder("Simulation");

  // Add pause simulation checkbox.
  // Parameters:
  //  Under "Simulation" folder.
  //  Name: "Pause Simulation".
  //  When paused, a "pause" text in white is displayed in the top left corner.
  //  Can also be triggered by pressing the spacebar.
  const pauseSimulation = simulationFolder.add(parentContext.params, 'paused').name('Pause Simulation');
  pauseSimulation.onChange((value) => {
    if (value) {
      const pausedText = document.createElement('div');
      pausedText.style.position = 'absolute';
      pausedText.style.top = '10px';
      pausedText.style.left = '10px';
      pausedText.style.color = 'white';
      pausedText.style.font = 'normal 18px Arial';
      pausedText.innerHTML = 'pause';
      parentContext.container.appendChild(pausedText);
    } else {
      parentContext.container.removeChild(parentContext.container.lastChild);
    }
  });
  document.addEventListener('keydown', (event) => {
    if (event.code === 'Space') {
      parentContext.params.paused = !parentContext.params.paused;
      pauseSimulation.setValue(parentContext.params.paused);
      event.preventDefault();
    }
  });
  actionInnerHTML += 'Play / Pause<br>';
  keyInnerHTML += 'Space<br>';

  // Add reload model button.
  // Parameters:
  //  Under "Simulation" folder.
  //  Name: "Reload".
  //  When pressed, calls the reload function.
  //  Can also be triggered by pressing ctrl + L.
  simulationFolder.add({reload: () => { reload(); }}, 'reload').name('Reload');
  document.addEventListener('keydown', (event) => {
    if (event.ctrlKey && event.code === 'KeyL') { reload();  event.preventDefault(); }});
  actionInnerHTML += 'Reload XML<br>';
  keyInnerHTML += 'Ctrl L<br>';

  // Add reset simulation button.
  // Parameters:
  //  Under "Simulation" folder.
  //  Name: "Reset".
  //  When pressed, resets the simulation to the initial state.
  //  Can also be triggered by pressing backspace.
  const resetSimulation = () => {
    parentContext.simulation.resetData();
    parentContext.simulation.forward();
  };
  simulationFolder.add({reset: () => { resetSimulation(); }}, 'reset').name('Reset');
  document.addEventListener('keydown', (event) => {
    if (event.code === 'Backspace') { resetSimulation(); event.preventDefault(); }});
  actionInnerHTML += 'Reset simulation<br>';
  keyInnerHTML += 'Backspace<br>';

  // Add keyframe slider.
  let nkeys = parentContext.model.nkey;
  let keyframeGUI = simulationFolder.add(parentContext.params, "keyframeNumber", 0, nkeys - 1, 1).name('Load Keyframe').listen();
  keyframeGUI.onChange((value) => {
    if (value < parentContext.model.nkey) {
      parentContext.simulation.qpos.set(parentContext.model.key_qpos.slice(
        value * parentContext.model.nq, (value + 1) * parentContext.model.nq)); }});
  parentContext.updateGUICallbacks.push((model, simulation, params) => {
    let nkeys = parentContext.model.nkey;
    console.log("new model loaded. has " + nkeys + " keyframes.");
    if (nkeys > 0) {
      keyframeGUI.max(nkeys - 1);
      keyframeGUI.domElement.style.opacity = 1.0;
    } else {
      // Disable keyframe slider if no keyframes are available.
      keyframeGUI.max(0);
      keyframeGUI.domElement.style.opacity = 0.5;
    }
  });

  // Add sliders for ctrlnoiserate and ctrlnoisestd; min = 0, max = 2, step = 0.01.
  simulationFolder.add(parentContext.params, 'ctrlnoiserate', 0.0, 2.0, 0.01).name('Noise rate' );
  simulationFolder.add(parentContext.params, 'ctrlnoisestd' , 0.0, 2.0, 0.01).name('Noise scale');

  let textDecoder = new TextDecoder("utf-8");
  let nullChar    = textDecoder.decode(new ArrayBuffer(1));

  // Add actuator sliders.
  let actuatorFolder = simulationFolder.addFolder("Actuators");
  const addActuators = (model, simulation, params) => {
    let act_range = model.actuator_ctrlrange;
    let actuatorGUIs = [];
    for (let i = 0; i < model.nu; i++) {
      if (!model.actuator_ctrllimited[i]) { continue; }
      let name = textDecoder.decode(
        parentContext.model.names.subarray(
          parentContext.model.name_actuatoradr[i])).split(nullChar)[0];

      parentContext.params[name] = 0.0;
      let actuatorGUI = actuatorFolder.add(parentContext.params, name, act_range[2 * i], act_range[2 * i + 1], 0.01).name(name).listen();
      actuatorGUIs.push(actuatorGUI);
      actuatorGUI.onChange((value) => {
        simulation.ctrl[i] = value;
      });
    }
    return actuatorGUIs;
  };
  let actuatorGUIs = addActuators(parentContext.model, parentContext.simulation, parentContext.params);
  parentContext.updateGUICallbacks.push((model, simulation, params) => {
    for (let i = 0; i < actuatorGUIs.length; i++) {
      actuatorGUIs[i].destroy();
    }
    actuatorGUIs = addActuators(model, simulation, parentContext.params);
  });
  actuatorFolder.close();

  // Add function that resets the camera to the default position.
  // Can be triggered by pressing ctrl + A.
  document.addEventListener('keydown', (event) => {
    if (event.ctrlKey && event.code === 'KeyA') {
      // TODO: Use free camera parameters from MuJoCo
      parentContext.camera.position.set(2.0, 1.7, 1.7);
      parentContext.controls.target.set(0, 0.7, 0);
      parentContext.controls.update(); 
      event.preventDefault();
    }
  });
  actionInnerHTML += 'Reset free camera<br>';
  keyInnerHTML += 'Ctrl A<br>';

  parentContext.gui.open();
}


/** Loads a scene for MuJoCo
 * @param {mujoco} mujoco This is a reference to the mujoco namespace object
 * @param {string} filename This is the name of the .xml file in the /working/ directory of the MuJoCo/Emscripten Virtual File System
 * @param {MuJoCoDemo} parent The three.js Scene Object to add the MuJoCo model elements to
 */
export async function loadSceneFromURL(mujoco, filename, parent) {
    // Free the old simulation.
    if (parent.simulation != null) {
      parent.simulation.free();
      parent.model      = null;
      parent.state      = null;
      parent.simulation = null;
    }

    // Load in the state from XML.
    parent.model       = mujoco.Model.load_from_xml("/working/"+filename);
    parent.state       = new mujoco.State(parent.model);
    parent.simulation  = new mujoco.Simulation(parent.model, parent.state);

    let model = parent.model;
    let state = parent.state;
    let simulation = parent.simulation;

    // Decode the null-terminated string names.
    let textDecoder = new TextDecoder("utf-8");
    let fullString = textDecoder.decode(model.names);
    let names = fullString.split(textDecoder.decode(new ArrayBuffer(1)));

    // Create the root object.
    let mujocoRoot = new THREE.Group();
    mujocoRoot.name = "MuJoCo Root"
    parent.scene.add(mujocoRoot);

    /** @type {Object.<number, THREE.Group>} */
    let bodies = {};
    /** @type {Object.<number, THREE.BufferGeometry>} */
    let meshes = {};
    /** @type {THREE.Light[]} */
    let lights = [];

    // Default material definition.
    let material = new THREE.MeshPhysicalMaterial();
    material.color = new THREE.Color(1, 1, 1);

    // Loop through the MuJoCo geoms and recreate them in three.js.
    for (let g = 0; g < model.ngeom; g++) {
      // Only visualize geom groups up to 2 (same default behavior as simulate).
      if (!(model.geom_group[g] < 3)) { continue; }

      // Get the body ID and type of the geom.
      let b = model.geom_bodyid[g];
      let type = model.geom_type[g];
      let size = [
        model.geom_size[(g*3) + 0],
        model.geom_size[(g*3) + 1],
        model.geom_size[(g*3) + 2]
      ];

      // Create the body if it doesn't exist.
      if (!(b in bodies)) {
        bodies[b] = new THREE.Group();
        bodies[b].name = names[model.name_bodyadr[b]];
        bodies[b].bodyID = b;
        bodies[b].has_custom_mesh = false;
      }

      // Set the default geometry. In MuJoCo, this is a sphere.
      let geometry = new THREE.SphereGeometry(size[0] * 0.5);
      if (type == mujoco.mjtGeom.mjGEOM_PLANE.value) {
        // Special handling for plane later.
      } else if (type == mujoco.mjtGeom.mjGEOM_HFIELD.value) {
        // TODO: Implement this.
      } else if (type == mujoco.mjtGeom.mjGEOM_SPHERE.value) {
        geometry = new THREE.SphereGeometry(size[0]);
      } else if (type == mujoco.mjtGeom.mjGEOM_CAPSULE.value) {
        geometry = new THREE.CapsuleGeometry(size[0], size[1] * 2.0, 20, 20);
      } else if (type == mujoco.mjtGeom.mjGEOM_ELLIPSOID.value) {
        geometry = new THREE.SphereGeometry(1); // Stretch this below
      } else if (type == mujoco.mjtGeom.mjGEOM_CYLINDER.value) {
        geometry = new THREE.CylinderGeometry(size[0], size[0], size[1] * 2.0);
      } else if (type == mujoco.mjtGeom.mjGEOM_BOX.value) {
        geometry = new THREE.BoxGeometry(size[0] * 2.0, size[2] * 2.0, size[1] * 2.0);
      } else if (type == mujoco.mjtGeom.mjGEOM_MESH.value) {
        let meshID = model.geom_dataid[g];

        if (!(meshID in meshes)) {
          geometry = new THREE.BufferGeometry(); // TODO: Populate the Buffer Geometry with Generic Mesh Data

          let vertex_buffer = model.mesh_vert.subarray(
             model.mesh_vertadr[meshID] * 3,
            (model.mesh_vertadr[meshID]  + model.mesh_vertnum[meshID]) * 3);
          for (let v = 0; v < vertex_buffer.length; v+=3){
            //vertex_buffer[v + 0] =  vertex_buffer[v + 0];
            let temp             =  vertex_buffer[v + 1];
            vertex_buffer[v + 1] =  vertex_buffer[v + 2];
            vertex_buffer[v + 2] = -temp;
          }

          let normal_buffer = model.mesh_normal.subarray(
             model.mesh_vertadr[meshID] * 3,
            (model.mesh_vertadr[meshID]  + model.mesh_vertnum[meshID]) * 3);
          for (let v = 0; v < normal_buffer.length; v+=3){
            //normal_buffer[v + 0] =  normal_buffer[v + 0];
            let temp             =  normal_buffer[v + 1];
            normal_buffer[v + 1] =  normal_buffer[v + 2];
            normal_buffer[v + 2] = -temp;
          }

          let uv_buffer = model.mesh_texcoord.subarray(
             model.mesh_texcoordadr[meshID] * 2,
            (model.mesh_texcoordadr[meshID]  + model.mesh_vertnum[meshID]) * 2);
          let triangle_buffer = model.mesh_face.subarray(
             model.mesh_faceadr[meshID] * 3,
            (model.mesh_faceadr[meshID]  + model.mesh_facenum[meshID]) * 3);
          geometry.setAttribute("position", new THREE.BufferAttribute(vertex_buffer, 3));
          geometry.setAttribute("normal"  , new THREE.BufferAttribute(normal_buffer, 3));
          geometry.setAttribute("uv"      , new THREE.BufferAttribute(    uv_buffer, 2));
          geometry.setIndex    (Array.from(triangle_buffer));
          meshes[meshID] = geometry;
        } else {
          geometry = meshes[meshID];
        }

        bodies[b].has_custom_mesh = true;
      }
      // Done with geometry creation.

      // Set the Material Properties of incoming bodies
      let texture = undefined;
      let color = [
        model.geom_rgba[(g * 4) + 0],
        model.geom_rgba[(g * 4) + 1],
        model.geom_rgba[(g * 4) + 2],
        model.geom_rgba[(g * 4) + 3]];
      if (model.geom_matid[g] != -1) {
        let matId = model.geom_matid[g];
        color = [
          model.mat_rgba[(matId * 4) + 0],
          model.mat_rgba[(matId * 4) + 1],
          model.mat_rgba[(matId * 4) + 2],
          model.mat_rgba[(matId * 4) + 3]];

        // Construct Texture from model.tex_rgb
        texture = undefined;
        let texId = model.mat_texid[matId];
        if (texId != -1) {
          let width    = model.tex_width [texId];
          let height   = model.tex_height[texId];
          let offset   = model.tex_adr   [texId];
          let rgbArray = model.tex_rgb   ;
          let rgbaArray = new Uint8Array(width * height * 4);
          for (let p = 0; p < width * height; p++){
            rgbaArray[(p * 4) + 0] = rgbArray[offset + ((p * 3) + 0)];
            rgbaArray[(p * 4) + 1] = rgbArray[offset + ((p * 3) + 1)];
            rgbaArray[(p * 4) + 2] = rgbArray[offset + ((p * 3) + 2)];
            rgbaArray[(p * 4) + 3] = 1.0;
          }
          texture = new THREE.DataTexture(rgbaArray, width, height, THREE.RGBAFormat, THREE.UnsignedByteType);
          if (texId == 2) {
            texture.repeat = new THREE.Vector2(50, 50);
            texture.wrapS = THREE.RepeatWrapping;
            texture.wrapT = THREE.RepeatWrapping;
          } else {
            texture.repeat = new THREE.Vector2(1, 1);
            texture.wrapS = THREE.RepeatWrapping;
            texture.wrapT = THREE.RepeatWrapping;
          }

          texture.needsUpdate = true;
        }
      }

      if (material.color.r != color[0] ||
          material.color.g != color[1] ||
          material.color.b != color[2] ||
          material.opacity != color[3] ||
          material.map     != texture) {
        material = new THREE.MeshPhysicalMaterial({
          color: new THREE.Color(color[0], color[1], color[2]),
          transparent: color[3] < 1.0,
          opacity: color[3],
          specularIntensity: model.geom_matid[g] != -1 ?       model.mat_specular   [model.geom_matid[g]] *0.5 : undefined,
          reflectivity     : model.geom_matid[g] != -1 ?       model.mat_reflectance[model.geom_matid[g]] : undefined,
          roughness        : model.geom_matid[g] != -1 ? 1.0 - model.mat_shininess  [model.geom_matid[g]] : undefined,
          metalness        : model.geom_matid[g] != -1 ? 0.1 : undefined,
          map              : texture
        });
      }

      let mesh = new THREE.Mesh();
      if (type == 0) {
        mesh = new Reflector( new THREE.PlaneGeometry( 100, 100 ), { clipBias: 0.003,texture: texture } );
        mesh.rotateX( - Math.PI / 2 );
      } else {
        mesh = new THREE.Mesh(geometry, material);
      }

      mesh.castShadow = g == 0 ? false : true;
      mesh.receiveShadow = type != 7;
      mesh.bodyID = b;
      bodies[b].add(mesh);
      getPosition  (model.geom_pos, g, mesh.position  );
      if (type != 0) { getQuaternion(model.geom_quat, g, mesh.quaternion); }
      if (type == 4) { mesh.scale.set(size[0], size[2], size[1]) } // Stretch the Ellipsoid
    }

    // Parse tendons.
    let tendonMat = new THREE.MeshPhongMaterial();
    tendonMat.color = new THREE.Color(0.8, 0.3, 0.3);
    mujocoRoot.cylinders = new THREE.InstancedMesh(
        new THREE.CylinderGeometry(1, 1, 1),
        tendonMat, 1023);
    mujocoRoot.cylinders.receiveShadow = true;
    mujocoRoot.cylinders.castShadow    = true;
    mujocoRoot.add(mujocoRoot.cylinders);
    mujocoRoot.spheres = new THREE.InstancedMesh(
        new THREE.SphereGeometry(1, 10, 10),
        tendonMat, 1023);
    mujocoRoot.spheres.receiveShadow = true;
    mujocoRoot.spheres.castShadow    = true;
    mujocoRoot.add(mujocoRoot.spheres);

    // Parse lights.
    for (let l = 0; l < model.nlight; l++) {
      let light = new THREE.SpotLight();
      if (model.light_directional[l]) {
        light = new THREE.DirectionalLight();
      } else {
        light = new THREE.SpotLight();
      }
      light.decay = model.light_attenuation[l] * 100;
      light.penumbra = 0.5;
      light.castShadow = true; // default false

      light.shadow.mapSize.width = 1024; // default
      light.shadow.mapSize.height = 1024; // default
      light.shadow.camera.near = 1; // default
      light.shadow.camera.far = 10; // default
      //bodies[model.light_bodyid()].add(light);
      if (bodies[0]) {
        bodies[0].add(light);
      } else {
        mujocoRoot.add(light);
      }
      lights.push(light);
    }
    if (model.nlight == 0) {
      let light = new THREE.DirectionalLight();
      mujocoRoot.add(light);
    }

    for (let b = 0; b < model.nbody; b++) {
      //let parent_body = model.body_parentid()[b];
      if (b == 0 || !bodies[0]) {
        mujocoRoot.add(bodies[b]);
      } else if(bodies[b]){
        bodies[0].add(bodies[b]);
      } else {
        console.log("Body without Geometry detected; adding to bodies", b, bodies[b]);
        bodies[b] = new THREE.Group(); bodies[b].name = names[b + 1]; bodies[b].bodyID = b; bodies[b].has_custom_mesh = false;
        bodies[0].add(bodies[b]);
      }
    }
  
    parent.mujocoRoot = mujocoRoot;

    return [model, state, simulation, bodies, lights]
}

/** Downloads the scenes/examples folder to MuJoCo's virtual filesystem
 * @param {mujoco} mujoco */
export async function downloadExampleScenesFolder(mujoco) {
  let allFiles = [
    "22_humanoids.xml",
    "adhesion.xml",
    "agility_cassie/assets/achilles-rod.obj",
    "agility_cassie/assets/cassie-texture.png",
    "agility_cassie/assets/foot-crank.obj",
    "agility_cassie/assets/foot.obj",
    "agility_cassie/assets/heel-spring.obj",
    "agility_cassie/assets/hip-pitch.obj",
    "agility_cassie/assets/hip-roll.obj",
    "agility_cassie/assets/hip-yaw.obj",
    "agility_cassie/assets/knee-spring.obj",
    "agility_cassie/assets/knee.obj",
    "agility_cassie/assets/pelvis.obj",
    "agility_cassie/assets/plantar-rod.obj",
    "agility_cassie/assets/shin.obj",
    "agility_cassie/assets/tarsus.obj",
    "agility_cassie/cassie.xml",
    "agility_cassie/scene.xml",
    "arm26.xml",
    "balloons.xml",
    "flag.xml",
    "hammock.xml",
    "humanoid.xml",
    "humanoid_body.xml",
    "model_with_tendon.xml",
    "mug.obj",
    "mug.png",
    "mug.xml",
    "scene.xml",
    "shadow_hand/assets/f_distal_pst.obj",
    "shadow_hand/assets/f_knuckle.obj",
    "shadow_hand/assets/f_middle.obj",
    "shadow_hand/assets/f_proximal.obj",
    "shadow_hand/assets/forearm_0.obj",
    "shadow_hand/assets/forearm_1.obj",
    "shadow_hand/assets/forearm_collision.obj",
    "shadow_hand/assets/lf_metacarpal.obj",
    "shadow_hand/assets/mounting_plate.obj",
    "shadow_hand/assets/palm.obj",
    "shadow_hand/assets/th_distal_pst.obj",
    "shadow_hand/assets/th_middle.obj",
    "shadow_hand/assets/th_proximal.obj",
    "shadow_hand/assets/wrist.obj",
    "shadow_hand/left_hand.xml",
    "shadow_hand/right_hand.xml",
    "shadow_hand/scene_left.xml",
    "simple.xml",
    "slider_crank.xml",
    "stompy/_env_dual_arm.xml",
    "stompy/_env_solo_arm.xml",
    "stompy/_env_torso.xml",
    "stompy/arm_l.xml",
    "stompy/arm_l_body copy.xml",
    "stompy/arm_l_body.xml",
    "stompy/arm_r.xml",
    "stompy/arm_r_body copy.xml",
    "stompy/arm_r_body.xml",
    "stompy/meshes/head_1_ardu_cam_mount_1.stl",
    "stompy/meshes/head_1_ardu_cam_mount_2.stl",
    "stompy/meshes/head_1_arducam_case_1.stl",
    "stompy/meshes/head_1_arducam_no_case_1.stl",
    "stompy/meshes/head_1_arducam_no_case_2.stl",
    "stompy/meshes/head_1_backplate_1.stl",
    "stompy/meshes/head_1_eye_1.stl",
    "stompy/meshes/head_1_eye_2.stl",
    "stompy/meshes/head_1_head_1.stl",
    "stompy/meshes/head_1_hear_platform_1.stl",
    "stompy/meshes/head_1_lcd_1.stl",
    "stompy/meshes/head_1_lcd_2.stl",
    "stompy/meshes/head_1_neck_1.stl",
    "stompy/meshes/head_1_x4_1_inner_1.stl",
    "stompy/meshes/head_1_x4_1_outer_1.stl",
    "stompy/meshes/head_1_x4_1_pcb_1.stl",
    "stompy/meshes/head_1_x4_2_inner_1.stl",
    "stompy/meshes/head_1_x4_2_outer_1.stl",
    "stompy/meshes/head_1_x4_2_pcb_1.stl",
    "stompy/meshes/head_1_xpt2046_touch_1.stl",
    "stompy/meshes/left_arm_2_elbow_1.stl",
    "stompy/meshes/left_arm_2_elbow_case_1.stl",
    "stompy/meshes/left_arm_2_forearm_1.stl",
    "stompy/meshes/left_arm_2_hand_1_arducam_case_1.stl",
    "stompy/meshes/left_arm_2_hand_1_base_1.stl",
    "stompy/meshes/left_arm_2_hand_1_camera_mount_1.stl",
    "stompy/meshes/left_arm_2_hand_1_gripper_1.stl",
    "stompy/meshes/left_arm_2_hand_1_gripper_2.stl",
    "stompy/meshes/left_arm_2_hand_1_mount_1.stl",
    "stompy/meshes/left_arm_2_hand_1_rack_1.stl",
    "stompy/meshes/left_arm_2_hand_1_rack_2.stl",
    "stompy/meshes/left_arm_2_hand_1_slide_1.stl",
    "stompy/meshes/left_arm_2_hand_1_slide_2.stl",
    "stompy/meshes/left_arm_2_hand_1_slide_rail_1.stl",
    "stompy/meshes/left_arm_2_hand_1_spur_gear_(26_teeth)_1.stl",
    "stompy/meshes/left_arm_2_hand_1_wrist_1.stl",
    "stompy/meshes/left_arm_2_hand_1_x4_1_inner_1.stl",
    "stompy/meshes/left_arm_2_hand_1_x4_1_outer_1.stl",
    "stompy/meshes/left_arm_2_hand_1_x4_1_pcb_1.stl",
    "stompy/meshes/left_arm_2_hand_1_x4_2_inner_1.stl",
    "stompy/meshes/left_arm_2_hand_1_x4_2_outer_1.stl",
    "stompy/meshes/left_arm_2_hand_1_x4_2_pcb_1.stl",
    "stompy/meshes/left_arm_2_hand_left_1_base_attachment_1.stl",
    "stompy/meshes/left_arm_2_hand_left_1_gripper_1.stl",
    "stompy/meshes/left_arm_2_hand_left_1_gripper_2.stl",
    "stompy/meshes/left_arm_2_hand_left_1_rack_1.stl",
    "stompy/meshes/left_arm_2_hand_left_1_rack_2.stl",
    "stompy/meshes/left_arm_2_hand_left_1_slide_1.stl",
    "stompy/meshes/left_arm_2_hand_left_1_slide_2.stl",
    "stompy/meshes/left_arm_2_hand_left_1_slide_rail_1.stl",
    "stompy/meshes/left_arm_2_hand_left_1_twist_mount_1.stl",
    "stompy/meshes/left_arm_2_hand_left_1_wrist_pitch_left_1.stl",
    "stompy/meshes/left_arm_2_hand_left_1_wrist_yaw_1.stl",
    "stompy/meshes/left_arm_2_hand_left_1_x4_1_inner_1.stl",
    "stompy/meshes/left_arm_2_hand_left_1_x4_1_outer_1.stl",
    "stompy/meshes/left_arm_2_hand_left_1_x4_1_pcb_1.stl",
    "stompy/meshes/left_arm_2_hand_left_1_x4_2_inner_1.stl",
    "stompy/meshes/left_arm_2_hand_left_1_x4_2_outer_1.stl",
    "stompy/meshes/left_arm_2_hand_left_1_x4_2_pcb_1.stl",
    "stompy/meshes/left_arm_2_hand_left_1_x4_3_inner_1.stl",
    "stompy/meshes/left_arm_2_hand_left_1_x4_3_outer_1.stl",
    "stompy/meshes/left_arm_2_hand_left_1_x4_3_pcb_1.stl",
    "stompy/meshes/left_arm_2_shoulder_inner_1.stl",
    "stompy/meshes/left_arm_2_shoulder_nontorso_1.stl",
    "stompy/meshes/left_arm_2_x4_1_inner_1.stl",
    "stompy/meshes/left_arm_2_x4_1_outer_1.stl",
    "stompy/meshes/left_arm_2_x4_1_pcb_1.stl",
    "stompy/meshes/left_arm_2_x6_1_inner_1.stl",
    "stompy/meshes/left_arm_2_x6_1_outer_1.stl",
    "stompy/meshes/left_arm_2_x6_1_pcb_1.stl",
    "stompy/meshes/left_arm_2_x6_2_inner_1.stl",
    "stompy/meshes/left_arm_2_x6_2_outer_1.stl",
    "stompy/meshes/left_arm_2_x6_2_pcb_1.stl",
    "stompy/meshes/left_arm_2_x8_1_inner_1.stl",
    "stompy/meshes/left_arm_2_x8_1_outer_1.stl",
    "stompy/meshes/left_arm_2_x8_1_pcb_1.stl",
    "stompy/meshes/left_arm_2_x8_2_inner_1.stl",
    "stompy/meshes/left_arm_2_x8_2_outer_1.stl",
    "stompy/meshes/left_arm_2_x8_2_pcb_1.stl",
    "stompy/meshes/legs_1_hips_1.stl",
    "stompy/meshes/legs_1_left_leg_1_51t_hdt5_15mm_belt_knee_left_1.stl",
    "stompy/meshes/legs_1_left_leg_1_ankle_1.stl",
    "stompy/meshes/legs_1_left_leg_1_ankle_pulley_48t_1.stl",
    "stompy/meshes/legs_1_left_leg_1_belt_thigh_left_1.stl",
    "stompy/meshes/legs_1_left_leg_1_calf_pulley_24t_1.stl",
    "stompy/meshes/legs_1_left_leg_1_foot_1.stl",
    "stompy/meshes/legs_1_left_leg_1_hip_rotate_1.stl",
    "stompy/meshes/legs_1_left_leg_1_rubber_1.stl",
    "stompy/meshes/legs_1_left_leg_1_thigh_htd_5mm_44t_pulley_1.stl",
    "stompy/meshes/legs_1_left_leg_1_thigh_rotate_left_1.stl",
    "stompy/meshes/legs_1_left_leg_1_x10_1_inner_1.stl",
    "stompy/meshes/legs_1_left_leg_1_x10_1_outer_1.stl",
    "stompy/meshes/legs_1_left_leg_1_x10_1_pcb_1.stl",
    "stompy/meshes/legs_1_left_leg_1_x10_2_inner_1.stl",
    "stompy/meshes/legs_1_left_leg_1_x10_2_outer_1.stl",
    "stompy/meshes/legs_1_left_leg_1_x10_2_pcb_1.stl",
    "stompy/meshes/legs_1_left_leg_1_x4_1_inner_1.stl",
    "stompy/meshes/legs_1_left_leg_1_x4_1_outer_1.stl",
    "stompy/meshes/legs_1_left_leg_1_x4_1_pcb_1.stl",
    "stompy/meshes/legs_1_left_leg_1_x6_1_inner_1.stl",
    "stompy/meshes/legs_1_left_leg_1_x6_1_outer_1.stl",
    "stompy/meshes/legs_1_left_leg_1_x6_1_pcb_1.stl",
    "stompy/meshes/legs_1_left_leg_1_x8_1_inner_1.stl",
    "stompy/meshes/legs_1_left_leg_1_x8_1_outer_1.stl",
    "stompy/meshes/legs_1_left_leg_1_x8_1_pcb_1.stl",
    "stompy/meshes/legs_1_right_leg_1_51t_hdt5_15mm_belt_knee_right_1.stl",
    "stompy/meshes/legs_1_right_leg_1_ankle_1.stl",
    "stompy/meshes/legs_1_right_leg_1_ankle_pulley_48t_1.stl",
    "stompy/meshes/legs_1_right_leg_1_belt_thigh_right_1.stl",
    "stompy/meshes/legs_1_right_leg_1_calf_pulley_24t_1.stl",
    "stompy/meshes/legs_1_right_leg_1_foot_1.stl",
    "stompy/meshes/legs_1_right_leg_1_hip_rotate_1.stl",
    "stompy/meshes/legs_1_right_leg_1_rubber_1.stl",
    "stompy/meshes/legs_1_right_leg_1_thigh_htd_5mm_44t_pulley_1.stl",
    "stompy/meshes/legs_1_right_leg_1_thigh_rotate_right_1.stl",
    "stompy/meshes/legs_1_right_leg_1_x10_1_inner_1.stl",
    "stompy/meshes/legs_1_right_leg_1_x10_1_outer_1.stl",
    "stompy/meshes/legs_1_right_leg_1_x10_1_pcb_1.stl",
    "stompy/meshes/legs_1_right_leg_1_x10_2_inner_1.stl",
    "stompy/meshes/legs_1_right_leg_1_x10_2_outer_1.stl",
    "stompy/meshes/legs_1_right_leg_1_x10_2_pcb_1.stl",
    "stompy/meshes/legs_1_right_leg_1_x4_1_inner_1.stl",
    "stompy/meshes/legs_1_right_leg_1_x4_1_outer_1.stl",
    "stompy/meshes/legs_1_right_leg_1_x4_1_pcb_1.stl",
    "stompy/meshes/legs_1_right_leg_1_x6_1_inner_1.stl",
    "stompy/meshes/legs_1_right_leg_1_x6_1_outer_1.stl",
    "stompy/meshes/legs_1_right_leg_1_x6_1_pcb_1.stl",
    "stompy/meshes/legs_1_right_leg_1_x8_1_inner_1.stl",
    "stompy/meshes/legs_1_right_leg_1_x8_1_outer_1.stl",
    "stompy/meshes/legs_1_right_leg_1_x8_1_pcb_1.stl",
    "stompy/meshes/legs_1_x8_1_inner_1.stl",
    "stompy/meshes/legs_1_x8_1_outer_1.stl",
    "stompy/meshes/legs_1_x8_1_pcb_1.stl",
    "stompy/meshes/legs_1_x8_2_inner_1.stl",
    "stompy/meshes/legs_1_x8_2_outer_1.stl",
    "stompy/meshes/legs_1_x8_2_pcb_1.stl",
    "stompy/meshes/right_arm_1_elbow_1.stl",
    "stompy/meshes/right_arm_1_elbow_case_1.stl",
    "stompy/meshes/right_arm_1_forearm_1.stl",
    "stompy/meshes/right_arm_1_hand_1_arducam_case_1.stl",
    "stompy/meshes/right_arm_1_hand_1_base_1.stl",
    "stompy/meshes/right_arm_1_hand_1_camera_mount_1.stl",
    "stompy/meshes/right_arm_1_hand_1_gripper_1.stl",
    "stompy/meshes/right_arm_1_hand_1_gripper_2.stl",
    "stompy/meshes/right_arm_1_hand_1_mount_1.stl",
    "stompy/meshes/right_arm_1_hand_1_rack_1.stl",
    "stompy/meshes/right_arm_1_hand_1_rack_2.stl",
    "stompy/meshes/right_arm_1_hand_1_slide_1.stl",
    "stompy/meshes/right_arm_1_hand_1_slide_2.stl",
    "stompy/meshes/right_arm_1_hand_1_slide_rail_1.stl",
    "stompy/meshes/right_arm_1_hand_1_spur_gear_(26_teeth)_1.stl",
    "stompy/meshes/right_arm_1_hand_1_wrist_1.stl",
    "stompy/meshes/right_arm_1_hand_1_x4_1_inner_1.stl",
    "stompy/meshes/right_arm_1_hand_1_x4_1_outer_1.stl",
    "stompy/meshes/right_arm_1_hand_1_x4_1_pcb_1.stl",
    "stompy/meshes/right_arm_1_hand_1_x4_2_inner_1.stl",
    "stompy/meshes/right_arm_1_hand_1_x4_2_outer_1.stl",
    "stompy/meshes/right_arm_1_hand_1_x4_2_pcb_1.stl",
    "stompy/meshes/right_arm_1_hand_right_1_base_attachment_1.stl",
    "stompy/meshes/right_arm_1_hand_right_1_gripper_1.stl",
    "stompy/meshes/right_arm_1_hand_right_1_gripper_2.stl",
    "stompy/meshes/right_arm_1_hand_right_1_rack_1.stl",
    "stompy/meshes/right_arm_1_hand_right_1_rack_2.stl",
    "stompy/meshes/right_arm_1_hand_right_1_slide_1.stl",
    "stompy/meshes/right_arm_1_hand_right_1_slide_2.stl",
    "stompy/meshes/right_arm_1_hand_right_1_slide_rail_1.stl",
    "stompy/meshes/right_arm_1_hand_right_1_twist_mount_1.stl",
    "stompy/meshes/right_arm_1_hand_right_1_wrist_pitch_right_2.stl",
    "stompy/meshes/right_arm_1_hand_right_1_wrist_yaw_1.stl",
    "stompy/meshes/right_arm_1_hand_right_1_x4_1_inner_1.stl",
    "stompy/meshes/right_arm_1_hand_right_1_x4_1_outer_1.stl",
    "stompy/meshes/right_arm_1_hand_right_1_x4_1_pcb_1.stl",
    "stompy/meshes/right_arm_1_hand_right_1_x4_2_inner_1.stl",
    "stompy/meshes/right_arm_1_hand_right_1_x4_2_outer_1.stl",
    "stompy/meshes/right_arm_1_hand_right_1_x4_2_pcb_1.stl",
    "stompy/meshes/right_arm_1_hand_right_1_x4_3_inner_1.stl",
    "stompy/meshes/right_arm_1_hand_right_1_x4_3_outer_1.stl",
    "stompy/meshes/right_arm_1_hand_right_1_x4_3_pcb_1.stl",
    "stompy/meshes/right_arm_1_shoulder_inner_1.stl",
    "stompy/meshes/right_arm_1_shoulder_nontorso_1.stl",
    "stompy/meshes/right_arm_1_x4_1_inner_1.stl",
    "stompy/meshes/right_arm_1_x4_1_outer_1.stl",
    "stompy/meshes/right_arm_1_x4_1_pcb_1.stl",
    "stompy/meshes/right_arm_1_x6_1_inner_1.stl",
    "stompy/meshes/right_arm_1_x6_1_outer_1.stl",
    "stompy/meshes/right_arm_1_x6_1_pcb_1.stl",
    "stompy/meshes/right_arm_1_x6_2_inner_1.stl",
    "stompy/meshes/right_arm_1_x6_2_outer_1.stl",
    "stompy/meshes/right_arm_1_x6_2_pcb_1.stl",
    "stompy/meshes/right_arm_1_x8_1_inner_1.stl",
    "stompy/meshes/right_arm_1_x8_1_outer_1.stl",
    "stompy/meshes/right_arm_1_x8_1_pcb_1.stl",
    "stompy/meshes/right_arm_1_x8_2_inner_1.stl",
    "stompy/meshes/right_arm_1_x8_2_outer_1.stl",
    "stompy/meshes/right_arm_1_x8_2_pcb_1.stl",
    "stompy/meshes/tabletop.stl",
    "stompy/meshes/torso_1_accelerometer_1.stl",
    "stompy/meshes/torso_1_battery_1.stl",
    "stompy/meshes/torso_1_battery_mount_1.stl",
    "stompy/meshes/torso_1_bottom_back_1.stl",
    "stompy/meshes/torso_1_bottom_torso_1.stl",
    "stompy/meshes/torso_1_breadboard_1.stl",
    "stompy/meshes/torso_1_mock_agx_orin_1.stl",
    "stompy/meshes/torso_1_pcb_1.stl",
    "stompy/meshes/torso_1_top_back_1.stl",
    "stompy/meshes/torso_1_top_torso_1.stl",
    "stompy/meshes/torso_1_x8_1_inner_1.stl",
    "stompy/meshes/torso_1_x8_1_outer_1.stl",
    "stompy/meshes/torso_1_x8_1_pcb_1.stl",
    "stompy/robot.xml",
    "stompy/scene.xml",
    "stompy/torso.xml",
    "stompy/torso_body.xml"
  ];

  let requests = allFiles.map((url) => fetch("./examples/scenes/" + url));
  let responses = await Promise.all(requests);
  for (let i = 0; i < responses.length; i++) {
      let split = allFiles[i].split("/");
      let working = '/working/';
      for (let f = 0; f < split.length - 1; f++) {
          working += split[f];
          if (!mujoco.FS.analyzePath(working).exists) { mujoco.FS.mkdir(working); }
          working += "/";
      }

      if (allFiles[i].endsWith(".png") || allFiles[i].endsWith(".stl") || allFiles[i].endsWith(".skn")) {
          mujoco.FS.writeFile("/working/" + allFiles[i], new Uint8Array(await responses[i].arrayBuffer()));
      } else {
          mujoco.FS.writeFile("/working/" + allFiles[i], await responses[i].text());
      }
  }
}

/** Access the vector at index, swizzle for three.js, and apply to the target THREE.Vector3
 * @param {Float32Array|Float64Array} buffer
 * @param {number} index
 * @param {THREE.Vector3} target */
export function getPosition(buffer, index, target, swizzle = true) {
  if (swizzle) {
    return target.set(
       buffer[(index * 3) + 0],
       buffer[(index * 3) + 2],
      -buffer[(index * 3) + 1]);
  } else {
    return target.set(
       buffer[(index * 3) + 0],
       buffer[(index * 3) + 1],
       buffer[(index * 3) + 2]);
  }
}

/** Access the quaternion at index, swizzle for three.js, and apply to the target THREE.Quaternion
 * @param {Float32Array|Float64Array} buffer
 * @param {number} index
 * @param {THREE.Quaternion} target */
export function getQuaternion(buffer, index, target, swizzle = true) {
  if (swizzle) {
    return target.set(
      -buffer[(index * 4) + 1],
      -buffer[(index * 4) + 3],
       buffer[(index * 4) + 2],
      -buffer[(index * 4) + 0]);
  } else {
    return target.set(
       buffer[(index * 4) + 0],
       buffer[(index * 4) + 1],
       buffer[(index * 4) + 2],
       buffer[(index * 4) + 3]);
  }
}

/** Converts this Vector3's Handedness to MuJoCo's Coordinate Handedness
 * @param {THREE.Vector3} target */
export function toMujocoPos(target) { return target.set(target.x, -target.z, target.y); }

/** Standard normal random number generator using Box-Muller transform */
export function standardNormal() {
  return Math.sqrt(-2.0 * Math.log( Math.random())) *
         Math.cos ( 2.0 * Math.PI * Math.random()); }

