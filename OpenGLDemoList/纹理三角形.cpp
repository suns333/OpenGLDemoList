////
////  纹理三角形.cpp
////  OpenGLDemoList
////
////  Created by 周洋 on 2020/7/20.
////  Copyright © 2020 周洋. All rights reserved.
////
//
//#include "GLTools.h"
//#include "GLShaderManager.h"
//#include "GLFrustum.h"
//#include "GLBatch.h"
//#include "GLFrame.h"
//#include "GLMatrixStack.h"
//#include "GLGeometryTransform.h"
//
//#ifdef __APPLE__
//#include <glut/glut.h>
//#else
//#define FREEGLUT_STATIC
//#include <GL/glut.h>
//#endif
//
//GLShaderManager        shaderManager;
//GLMatrixStack        modelViewMatrix;
//GLMatrixStack        projectionMatrix;
//GLFrame                cameraFrame;
//GLFrame             objectFrame;
//GLFrustum            viewFrustum;
//
//GLBatch             pyramidBatch;
//
////纹理变量，一般使用无符号整型
//GLuint              textureID;
//
//GLGeometryTransform    transformPipeline;
//M3DMatrix44f        shadowMatrix;
//
////绘制金字塔
//void MakePyramid(GLBatch& pyramidBatch) {
//    pyramidBatch.Begin(GL_TRIANGLES, 18, 1);
//
//    //塔顶
//    M3DVector3f vApex = { 0.0f, 1.0f, 0.0f };
//    M3DVector3f vFrontLeft = { -1.0f, -1.0f, 1.0f };
//    M3DVector3f vFrontRight = { 1.0f, -1.0f, 1.0f };
//    M3DVector3f vBackLeft = { -1.0f,  -1.0f, -1.0f };
//    M3DVector3f vBackRight = { 1.0f,  -1.0f, -1.0f };
//
//    //金字塔底部
//    //底部的四边形 = 三角形X + 三角形Y
//    //三角形X = (vBackLeft,vBackRight,vFrontRight)
//    //vBackLeft
//    pyramidBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
//    pyramidBatch.Vertex3fv(vBackLeft);
//
//    //vBackRight
//    pyramidBatch.MultiTexCoord2f(0, 1.0f, 0.0f);
//    pyramidBatch.Vertex3fv(vBackRight);
//
//    //vFrontRight
//    pyramidBatch.MultiTexCoord2f(0, 1.0f, 1.0f);
//    pyramidBatch.Vertex3fv(vFrontRight);
//
//
//    //三角形Y =(vFrontLeft,vBackLeft,vFrontRight)
//    //vFrontLeft
//    pyramidBatch.MultiTexCoord2f(0, 0.0f, 1.0f);
//    pyramidBatch.Vertex3fv(vFrontLeft);
//
//    //vBackLeft
//    pyramidBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
//    pyramidBatch.Vertex3fv(vBackLeft);
//
//    //vFrontRight
//    pyramidBatch.MultiTexCoord2f(0, 1.0f, 1.0f);
//    pyramidBatch.Vertex3fv(vFrontRight);
//
//
//    // 金字塔前面
//    //三角形：（Apex，vFrontLeft，vFrontRight）
//    pyramidBatch.MultiTexCoord2f(0, 0.5f, 1.0f);
//    pyramidBatch.Vertex3fv(vApex);
//
//    pyramidBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
//    pyramidBatch.Vertex3fv(vFrontLeft);
//
//    pyramidBatch.MultiTexCoord2f(0, 1.0f, 0.0f);
//    pyramidBatch.Vertex3fv(vFrontRight);
//
//    //金字塔左边
//    //三角形：（vApex, vBackLeft, vFrontLeft）
//    pyramidBatch.MultiTexCoord2f(0, 0.5f, 1.0f);
//    pyramidBatch.Vertex3fv(vApex);
//
//    pyramidBatch.MultiTexCoord2f(0, 1.0f, 0.0f);
//    pyramidBatch.Vertex3fv(vBackLeft);
//
//    pyramidBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
//    pyramidBatch.Vertex3fv(vFrontLeft);
//
//    //金字塔右边
//    //三角形：（vApex, vFrontRight, vBackRight）
//    pyramidBatch.MultiTexCoord2f(0, 0.5f, 1.0f);
//    pyramidBatch.Vertex3fv(vApex);
//
//    pyramidBatch.MultiTexCoord2f(0, 1.0f, 0.0f);
//    pyramidBatch.Vertex3fv(vFrontRight);
//
//    pyramidBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
//    pyramidBatch.Vertex3fv(vBackRight);
//
//    //金字塔后边
//    //三角形：（vApex, vBackRight, vBackLeft）
//    pyramidBatch.MultiTexCoord2f(0, 0.5f, 1.0f);
//    pyramidBatch.Vertex3fv(vApex);
//
//    pyramidBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
//    pyramidBatch.Vertex3fv(vBackRight);
//
//    pyramidBatch.MultiTexCoord2f(0, 1.0f, 0.0f);
//    pyramidBatch.Vertex3fv(vBackLeft);
//
//    //结束批次设置
//    pyramidBatch.End();
//}
//
//// 将TGA文件加载为2D纹理。
//bool LoadTGATexture(const char *szFileName, GLenum minFilter, GLenum magFilter, GLenum wrapMode) {
//    GLbyte *pBits;
//    int nWidth, nHeight, nComponets;
//    GLenum eFormat;
//
//    pBits = gltReadTGABits(szFileName, &nWidth, &nHeight, &nComponets, &eFormat);
//    if(pBits == NULL) return false;
//
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
//
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
//
//    glTexImage2D(GL_TEXTURE_2D, 0, nComponets, nWidth, nHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBits);
//
//    free(pBits);
//
//    glGenerateMipmap(GL_TEXTURE_2D);
//    return true;
//}
//
//void SetupRC() {
//    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
//    glEnable(GL_DEPTH_TEST);
//    shaderManager.InitializeStockShaders();
//
//    //分配纹理对象
//    glGenTextures(1, &textureID);
//    //绑定纹理状态
//    glBindTexture(GL_TEXTURE_2D, textureID);
//    //加载纹理
//    LoadTGATexture("brick.tga", GL_LINEAR_MIPMAP_NEAREST, GL_LINEAR, GL_CLAMP_TO_EDGE);
//    MakePyramid(pyramidBatch);
//
//    cameraFrame.MoveForward(-10);
//}
//
//void ShutdownRC(void) {
//    glDeleteTextures(1, &textureID);
//}
//
//void RenderScene(void) {
//
//    //1.颜色值&光源位置
//    static GLfloat vLightPos [] = { 1.0f, 1.0f, 0.0f };
//    static GLfloat vWhite [] = { 1.0f, 1.0f, 1.0f, 1.0f };
//
//    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
//
//    modelViewMatrix.PushMatrix();
//    M3DMatrix44f mCamera;
//    cameraFrame.GetCameraMatrix(mCamera);
//    modelViewMatrix.MultMatrix(mCamera);
//
//    M3DMatrix44f mObjectFrame;
//    objectFrame.GetMatrix(mObjectFrame);
//    modelViewMatrix.MultMatrix(mObjectFrame);
//
//    glBindTexture(GL_TEXTURE_2D, textureID);
//
//    shaderManager.UseStockShader(GLT_SHADER_TEXTURE_REPLACE, transformPipeline.GetModelViewProjectionMatrix(), 0);
//
//    pyramidBatch.Draw();
//
//    glutSwapBuffers();
//}
//
//void SpecialKeys(int key, int x, int y) {
//    if(key == GLUT_KEY_UP) {
//        //        objectFrame.RotateWorld(m3dDegToRad(-5.0f), 1.0f, 0.0f, 0.0f);
//        objectFrame.MoveUp(0.5f);
//        cameraFrame.MoveUp(0.5f);
//    }
//
//    if(key == GLUT_KEY_DOWN) {
//        //        objectFrame.RotateWorld(m3dDegToRad(5.0f), 1.0f, 0.0f, 0.0f);
//        objectFrame.MoveUp(-0.5f);
//        cameraFrame.MoveUp(-0.5f);
//    }
//
//    if(key == GLUT_KEY_LEFT) {
//        //        objectFrame.RotateWorld(m3dDegToRad(-5.0f), 0.0f, 1.0f, 0.0f);
//        objectFrame.MoveRight(0.5f);
//        cameraFrame.MoveRight(-0.5f);
//    }
//
//    if(key == GLUT_KEY_RIGHT) {
//        //        objectFrame.RotateWorld(m3dDegToRad(5.0f), 0.0f, 1.0f, 0.0f);
//        //        objectFrame.MoveRight(-0.5f);
//        cameraFrame.MoveRight(0.5f);
//    }
//    glutPostRedisplay();
//
//}
//
//void ChangeSize(int w, int h) {
//    glViewport(0, 0, w, h);
//
//    viewFrustum.SetPerspective(35.0f, float(w)/float(h), 1, 100.0f);
//    projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
//
//    modelViewMatrix.LoadIdentity();
//
//    transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
//}
//
//int main(int argc, char* argv[])
//{
//    gltSetWorkingDirectory(argv[0]);
//
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
//    glutInitWindowSize(800, 600);
//    glutCreateWindow("Pyramid");
//    glutReshapeFunc(ChangeSize);
//    glutSpecialFunc(SpecialKeys);
//    glutDisplayFunc(RenderScene);
//
//    GLenum err = glewInit();
//    if (GLEW_OK != err) {
//        fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
//        return 1;
//    }
//
//
//    SetupRC();
//
//    glutMainLoop();
//
//    ShutdownRC();
//
//    return 0;
//}
