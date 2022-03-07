import bpy
import gpu

class PointShader :
    def __init__(self) :
        self.__shader = None

    def get_shader(self) :
        return self.__shader

    def exists(self) :
        return self.__shader != None

    def build(self, scene) :        
        vertex_shader = """
                    uniform mat4 MVPMatrix;
                    in vec3 pos;
                    in vec4 color;

                    out vec4 vColor;

                    void main()
                    {
                        gl_Position = MVPMatrix * vec4(pos, 1.0);
                        vColor = color;
                    }
        """

        fragment_shader = """
                    in vec4 vColor;

                    void main()
                    {
                        gl_FragColor = vColor;
                    }
        """
        self.__shader = gpu.types.GPUShader(vertex_shader, fragment_shader)
