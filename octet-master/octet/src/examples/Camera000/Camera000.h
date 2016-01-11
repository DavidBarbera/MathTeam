////////////////////////////////////////////////////////////////////////////////
//
// (C) Andy Thomason 2012-2014
//
// Modular Framework for OpenGLES2 rendering on multiple platforms.
//

#define SPEED 1.0f

namespace octet {
  /// Scene containing a box with octet.
	class Camera000 : public app {
		// scene for drawing box
		ref<visual_scene> app_scene;

		ref<camera_instance> camera;
		vec3 cameraPos;
		ref<scene_node> camera_node;


	public:
		Camera000(int argc, char **argv) : app(argc, argv) {
		}

		~Camera000() {
		}

		/// this is called once OpenGL is initialized
		void app_init() {
			app_scene = new visual_scene();
			app_scene->create_default_camera_and_lights();


			// the camera
			app_scene->get_camera_instance(0)->get_node()->translate(vec3(0, 4, 0));
			camera = app_scene->get_camera_instance(0);

			camera_node = camera->get_node();
			mat4t &camera_to_world = camera_node->access_nodeToParent();



			material *red = new material(vec4(1, 0, 0, 1));
			material *green = new material(vec4(0, 1, 0, 1));
			material *blue = new material(vec4(0, 0, 1, 1));

			mat4t mat;
			mat.translate(-3, 6, 0);
			app_scene->add_shape(mat, new mesh_sphere(vec3(2, 2, 2), 2), red, true);

			mat.loadIdentity();
			mat.translate(0, 10, 0);
			app_scene->add_shape(mat, new mesh_box(vec3(2, 2, 2)), red, true);

			mat.loadIdentity();
			mat.translate(3, 6, 0);
			app_scene->add_shape(mat, new mesh_cylinder(zcylinder(vec3(0, 0, 0), 2, 4)), blue, true);

			// ground
			mat.loadIdentity();
			mat.translate(0, -1, 0);
			app_scene->add_shape(mat, new mesh_box(vec3(200, 1, 200)), green, false);
		}

		/// this is called to draw the world
		void draw_world(int x, int y, int w, int h) {
			int vx = 0, vy = 0;
			get_viewport_size(vx, vy);
			app_scene->begin_render(vx, vy);

			// update matrices. assume 30 fps.
			app_scene->update(1.0f / 30);

			// draw the scene
			app_scene->render((float)vx / vy);

			//camera movement
			if (is_key_down(key_left))
			{
				camera_node->translate(vec3(-SPEED, 0, 0));
			}
			if (is_key_down(key_right))
			{
				camera_node->translate(vec3(SPEED, 0, 0));
			}
			if (is_key_down(key_up))
			{
				camera_node->translate(vec3(0, 0, -SPEED));
			}
			if (is_key_down(key_down))
			{
				camera_node->translate(vec3(0, 0, SPEED));
			}
			if (is_key_down('D'))
			{
				camera_node->rotate(-SPEED,vec3(0, 1, 0));
			}
			if (is_key_down('A'))
			{
				camera_node->rotate(SPEED, vec3(0, 1, 0));
			}
			if (is_key_down('W'))
			{
				camera_node->rotate(SPEED, vec3(1, 0, 0));
			}
			if (is_key_down('S'))
			{
				camera_node->rotate(-SPEED, vec3(1, 0, 0));
			}


		}
	};
}
