//
//  公转自转.cpp
//  OpenGLDemoList
//
//  Created by 周洋 on 2020/7/18.
//  Copyright © 2020 周洋. All rights reserved.
//

#include <GLTools.h>
#include <GLShaderManager.h>
#include <GLFrustum.h>
#include <GLBatch.h>
#include <GLFrame.h>
#include <GLMatrixStack.h>
#include <GLGeometryTransform.h>
#include <StopWatch.h>

#include <math.h>
#include <stdio.h>

#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

//**4、添加附加随机球
#define NUM_SPHERES 50
GLFrame spheres[NUM_SPHERES];

GLShaderManager        shaderManager;            // 着色器管理器
GLMatrixStack        modelViewMatrix;        // 模型视图矩阵
GLMatrixStack        projectionMatrix;        // 投影矩阵
GLFrustum            viewFrustum;            // 视景体
GLGeometryTransform    transformPipeline;        // 几何图形变换管道

GLTriangleBatch        torusBatch;             // 花托批处理
GLBatch                floorBatch;             // 地板批处理

//**2、定义公转球的批处理（公转自转）**
GLTriangleBatch     sphereBatch;            //球批处理

//**3、角色帧 照相机角色帧（全局照相机实例）
GLFrame             cameraFrame;

//**5、添加纹理
//纹理标记数组
GLuint uiTextures[3];

bool LoadTGATexture(const char *szFileName, GLenum minFilter, GLenum magFilter, GLenum wrapMode) {
    GLbyte *pBits;
    GLint nWidth,nHeight,nComponents;
    GLenum eFormat;
    //读取tga文件，获取对应的宽度、高度等数据
    pBits = gltReadTGABits(szFileName, &nWidth, &nHeight, &nComponents, &eFormat);
    if(pBits == NULL) return false;
    
    //设置环绕模式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
    //设置过滤模式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    //加载纹理
    glTexImage2D(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGB, nWidth, nHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBits);
    free(pBits);
    
    if(minFilter == GL_LINEAR_MIPMAP_LINEAR ||
       minFilter == GL_LINEAR_MIPMAP_NEAREST ||
       minFilter == GL_NEAREST_MIPMAP_LINEAR ||
       minFilter == GL_NEAREST_MIPMAP_NEAREST) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    return true;
}


void ChangeSize(int w, int h) {
    glViewport(0, 0, w, h);

    viewFrustum.SetPerspective(35.0f, float(w)/float(h), 1, 500);
    projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());

    modelViewMatrix.LoadIdentity();
    transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
}

void drawSomething(GLfloat yRot, bool up) {
    static GLfloat vWhite[] = {1.0f, 1.0f, 1.0f, 1};
    GLfloat vLightPos[] = {0.0f, up?3.0f:-3.0f, 0.0f, 1.0f};
    
    //画随机的小球
    glBindTexture(GL_TEXTURE_2D, uiTextures[2]);
    for(int i = 0; i < NUM_SPHERES; i++) {
        modelViewMatrix.PushMatrix();
        modelViewMatrix.MultMatrix(spheres[i]);
        shaderManager.UseStockShader(GLT_SHADER_TEXTURE_POINT_LIGHT_DIFF, transformPipeline.GetModelViewMatrix(), transformPipeline.GetProjectionMatrix(), vLightPos, vWhite, 0);
        sphereBatch.Draw();
        modelViewMatrix.PopMatrix();
    }
    
    modelViewMatrix.Translate(0, 0.2f, -2.5f);
    modelViewMatrix.PushMatrix();
    //画自转的大球
    modelViewMatrix.Rotate(yRot, 0, 1.0f, 0.f);
    glBindTexture(GL_TEXTURE_2D, uiTextures[1]);
    shaderManager.UseStockShader(GLT_SHADER_TEXTURE_POINT_LIGHT_DIFF, transformPipeline.GetModelViewMatrix(), transformPipeline.GetProjectionMatrix(), vLightPos, vWhite, 0);
    torusBatch.Draw();
    modelViewMatrix.PopMatrix();
    
    modelViewMatrix.PushMatrix();
    //画公转的小球
    modelViewMatrix.Rotate(-yRot, 0, 1.0f, 0);
    modelViewMatrix.Translate(0.8f, 0, 0);
    glBindTexture(GL_TEXTURE_2D, uiTextures[2]);
    shaderManager.UseStockShader(GLT_SHADER_TEXTURE_POINT_LIGHT_DIFF, transformPipeline.GetModelViewMatrix(), transformPipeline.GetProjectionMatrix(), vLightPos, vWhite, 0);
    sphereBatch.Draw();
    modelViewMatrix.PopMatrix();
}

void RenderScene() {
    static GLfloat vFloorColor[] = {1.0f, 1.0f, 0.0f, 0.75f};
    static CStopWatch rotTimer;
    GLfloat yRot = rotTimer.GetElapsedSeconds()*60.0f;
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    modelViewMatrix.PushMatrix();
    M3DMatrix44f mCamera;
    cameraFrame.GetCameraMatrix(mCamera);
    modelViewMatrix.MultMatrix(mCamera);
    
    modelViewMatrix.PushMatrix();
    modelViewMatrix.Scale(1.0, -1, 1.0);
    modelViewMatrix.Translate(0, 0.8f, 0);
    
    glFrontFace(GL_CW);
    drawSomething(yRot, false);
    glFrontFace(GL_CCW);
    modelViewMatrix.PopMatrix();
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glBindTexture(GL_TEXTURE_2D, uiTextures[0]);
    shaderManager.UseStockShader(GLT_SHADER_TEXTURE_MODULATE, transformPipeline.GetModelViewProjectionMatrix(), vFloorColor, 0);
    floorBatch.Draw();
    glDisable(GL_BLEND);
    
    drawSomething(yRot, true);
    modelViewMatrix.PopMatrix();
    
    glutSwapBuffers();
    
    glutPostRedisplay();
}

void SpecialKeys(int key, int x, int y) {
    GLfloat linear = 0.1f;
    GLfloat angular = GLfloat(m3dDegToRad(5.0f));
    if(key == GLUT_KEY_UP) {
//        cameraFrame.MoveForward(linear);
        cameraFrame.MoveUp(linear);
    }
    if(key == GLUT_KEY_DOWN) {
//        cameraFrame.MoveForward(-linear);
        cameraFrame.MoveUp(-linear);
    }
    if(key == GLUT_KEY_LEFT) {
        cameraFrame.RotateWorld(angular, 0, 1, 0);
    }
    if(key == GLUT_KEY_RIGHT) {
        cameraFrame.RotateWorld(-angular, 0, 1, 0);
    }
    glutPostRedisplay();
}

void SetupRC() {
    glClearColor(0.0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);
    shaderManager.InitializeStockShaders();

    //设置大球
    gltMakeSphere(torusBatch, 0.4f, 40, 80);
    //设置小球
    gltMakeSphere(sphereBatch, 0.1f, 26, 13);
    
    GLfloat texSize = 10.f;
    floorBatch.Begin(GL_TRIANGLE_FAN, 4, 1);
    
    floorBatch.MultiTexCoord2f(0, texSize, 0);
    floorBatch.Vertex3f(-20.f, -0.41, 20.f);
    
    floorBatch.MultiTexCoord2f(0, texSize, texSize);
    floorBatch.Vertex3f(20, -0.41, 20);
    
    floorBatch.MultiTexCoord2f(0, 0, texSize);
    floorBatch.Vertex3f(20.f, -0.41, -20.f);
    
    floorBatch.MultiTexCoord2f(0, 0.0f, 0);
    floorBatch.Vertex3f(-20, -0.41, -20.f);
    
    floorBatch.End();
    
    for(int i = 0; i < NUM_SPHERES; i++) {
        GLfloat x = (rand()%400-200)*0.1f;
        GLfloat z = (rand()%400-200)*0.1f;
        
        spheres[i].SetOrigin(x, 0.0f, z);
    }
    
    glGenTextures(3, uiTextures);
    
    glBindTexture(GL_TEXTURE_2D, uiTextures[0]);
    LoadTGATexture("douzhi.tga", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);
    
    glBindTexture(GL_TEXTURE_2D, uiTextures[1]);
    LoadTGATexture("marslike.tga", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);
    
    glBindTexture(GL_TEXTURE_2D, uiTextures[2]);
    LoadTGATexture("test.tga", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);
}

//删除纹理
void ShutdownRC(void)
{
    glDeleteTextures(3, uiTextures);
}

int main(int argc, char* argv[]) {
    gltSetWorkingDirectory(argv[0]);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB);
    glutInitWindowSize(800,600);
    glutCreateWindow("公转自转");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    glutSpecialFunc(SpecialKeys);

    GLenum err = glewInit();
    if(err != GLEW_OK) {
        fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
        return 1;
    }
    SetupRC();
    glutMainLoop();
    ShutdownRC();

    return 0;
}
