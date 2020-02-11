#include "personal_objects/bObject.hpp"
#include <sys/time.h> 
#include <type_traits>
#include <typeinfo>

bObject::bObject(BasicsBlock* bc, Camera* m_camera ,float initial_pos[3]):GameObject
(bc,m_camera,initial_pos){
    m_camera->camera_pos = new glm::vec3(-3.0f,2.0f,10.0f);
    yaw = -75.0f;
    pitch = -15.0f;
    sensitivity= 0.125;
    camera_front = glm::vec3(0,0,-1);
    lastX = m_window->GetWidth()/2;
    lastY = m_window->GetHeight()/2;
    m_deque_test = new std::deque<char*>();
    fov = 45;
    didExit = false;
    /*===============GUI=====================*/
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_window->GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

void bObject::Ready(){
    obj_iterator = bb->all_objs->begin();
}

void bObject::Update(){
    if (m_input->ProcessInput(GLFW_KEY_LEFT_CONTROL,GLFW_PRESS)){
        yaw = -75;
        pitch = -15;
         camera_front = glm::vec3(0,0,-1);
         m_camera->camera_pos->x = -3.0f;
         m_camera->camera_pos->y = 2.0f;
         m_camera->camera_pos->z = 10;
         fov = 45;
         m_camera->MakeProjection(glm::radians(fov));
    }

    #ifdef __unix__
    //BE CAREFULL WHEN USING THIS, IT SIMULATES MEMORY LEAK
    if(m_input->ProcessInput(GLFW_KEY_9,GLFW_PRESS)){
        m_deque_test->push_back((char*) malloc (1000000) );
    }
    //THIS CLEANS THE WASTED MEMORY
    if(m_input->ProcessInput(GLFW_KEY_0,GLFW_PRESS)){
        for(int i = 0; i < m_deque_test->size(); i++){
            delete m_deque_test->at(i);
        }
        m_deque_test->clear();
    }
    #endif
    
    if(show_cursor == GLFW_CURSOR_DISABLED) CalculateCam();
    if(show_cursor == GLFW_CURSOR_NORMAL) RenderGUI();

    if(this->m_input->ProcessInput(GLFW_KEY_LEFT_SHIFT,GLFW_PRESS)){
        this->test_speed = 15;
    }
    if(this->m_input->ProcessInput(GLFW_KEY_D,GLFW_PRESS)){
        *m_camera->camera_pos += glm::normalize(glm::cross(*m_camera->camera_front, *m_camera->camera_up)) * (float)(test_speed * m_time->delta_time); 
  
    }else if(this->m_input->ProcessInput(GLFW_KEY_A,GLFW_PRESS)){  
        *m_camera->camera_pos -= glm::normalize(glm::cross(*m_camera->camera_front, *m_camera->camera_up)) * (float)(test_speed * m_time->delta_time); 
    }
    if(this->m_input->ProcessInput(GLFW_KEY_S,GLFW_PRESS)){
        *m_camera->camera_pos -= (float)(test_speed * m_time->delta_time) * *m_camera->camera_front;

    }else if(this->m_input->ProcessInput(GLFW_KEY_W,GLFW_PRESS)){
        *m_camera->camera_pos += (float)(test_speed * m_time->delta_time) * *m_camera->camera_front;
    }

    else if(this->m_input->ProcessInput(GLFW_KEY_1,GLFW_PRESS)){
        Debugging::SetPoly2Fill();
    }else if(this->m_input->ProcessInput(GLFW_KEY_2,GLFW_PRESS)){
        Debugging::SetPoly2Line();
    }
    else if(this->m_input->ProcessInput(GLFW_KEY_3,GLFW_PRESS)){
        Debugging::SetPoly2Points();
    }

    m_camera->camera_front = &camera_front;
    m_camera->LookAt(*m_camera->camera_pos+ *m_camera->camera_front);

    this->test_speed = 5;

    if(m_input->ProcessInput(GLFW_KEY_F1) && f1KeyRealeased){
        show_cursor = show_cursor == GLFW_CURSOR_DISABLED? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED;
        glfwSetInputMode(m_window->GetWindow(),GLFW_CURSOR,show_cursor);
        f1KeyRealeased = false;
        if(show_cursor == GLFW_CURSOR_DISABLED){
            lastX = m_input->mouse_Xpos;
            lastY = m_input->mouse_Ypos;
        }
        
    }else if (m_input->ProcessInput(GLFW_KEY_F1,GLFW_RELEASE)){
        f1KeyRealeased = true;
    }
}

void bObject::RenderGUI(){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    {
        static float vec_pos[3];
        static float *vec_color;
        ImGui::Begin("Game Object Manipulator");
        ImGui::Text("Select Object Name: %s", (*obj_iterator)->object_name.c_str());
        if(ImGui::Button("<<")){
            if(obj_iterator != bb->all_objs->begin()){
                obj_iterator--;
            }
        }
        ImGui::SameLine();
        if (ImGui::Button(">>")){
            if(obj_iterator != --bb->all_objs->end()){
                obj_iterator++;
            }
        }
        vec_pos[0] = (*obj_iterator)->model[3][0];
        vec_pos[1] = (*obj_iterator)->model[3][1];
        vec_pos[2] = (*obj_iterator)->model[3][2];
        ImGui::SliderFloat3("Object position", vec_pos,-5.0,5.0);
        (*obj_iterator)->model[3][0] = vec_pos[0];
        (*obj_iterator)->model[3][1] = vec_pos[1];
        (*obj_iterator)->model[3][2] = vec_pos[2];

        if ((*obj_iterator)->m_material != nullptr){
            vec_color = glm::value_ptr((*obj_iterator)->m_material->diffuse_color);
            ImGui::ColorEdit3("Material Color", vec_color);
            (*obj_iterator)->m_material->ambient_color[0] = (*obj_iterator)->m_material->diffuse_color[0];
            (*obj_iterator)->m_material->ambient_color[1] = (*obj_iterator)->m_material->diffuse_color[1];
            (*obj_iterator)->m_material->ambient_color[2] = (*obj_iterator)->m_material->diffuse_color[2];
           
        }
        ImGui::NewLine();
        ImGui::Separator();
        ImGui::NewLine();
        if((*obj_iterator)->m_light != nullptr){
            vec_color = glm::value_ptr((*obj_iterator)->m_light->light_color);
            ImGui::ColorEdit3("Light Color", vec_color);
            ImGui::SliderFloat("Light Intensity",&(*obj_iterator)->m_light->light_intensity,0.0f,1.0f);
        }
        
        ImGui::End();
    }

    /*
    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
    {
        // Our state
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Another Window", &show_another_window);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Text("Aproximated Memory usage(%.d )",Debugging::GetMemoryUsage());
        ImGui::End();
    }
    if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }
    */
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void bObject::CalculateCam(){
    if(firstMouse && m_input->isMouseReady){
        lastX = m_input->mouse_Xpos;
        lastY = m_input->mouse_Ypos;
        firstMouse = false;
    }

    if(!m_input->is_cursor_in){
        didExit = true;
    }

    if(didExit && m_input->is_cursor_in){
        lastX = m_input->mouse_Xpos;
        lastY = m_input->mouse_Ypos;
        didExit = false;
    }

    float xoffset = m_input->mouse_Xpos - lastX;
    float yoffset = lastY - m_input->mouse_Ypos;
    if(!firstMouse && !didExit && (abs(xoffset) > 0.1f ||  abs(yoffset) > 0.1f)){
        lastX = m_input->mouse_Xpos;
        lastY = m_input->mouse_Ypos;
        xoffset *= sensitivity;
        yoffset *= sensitivity;m_input;

        yaw += xoffset;
        pitch += yoffset;

        pitch = pitch > 89.4f ? 89.4f : pitch < -89.4f ? -89.4f :  pitch; 
    }
    
    camera_front.y = sin(glm::radians(pitch));
    camera_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    camera_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    camera_front = glm::normalize(camera_front);
    fov -= m_input->scroll_y * (sensitivity * 20);
    fov = fov > 110 ? 110 : fov < 1 ? 1 : fov;
    m_camera->MakeProjection(glm::radians(fov));


}