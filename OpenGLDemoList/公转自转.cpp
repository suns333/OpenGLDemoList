////
////  公转自转.cpp
////  OpenGLDemoList
////
////  Created by 周洋 on 2020/7/18.
////  Copyright © 2020 周洋. All rights reserved.
////
//
//#include <GLTools.h>
//#include <GLShaderManager.h>
//#include <GLFrustum.h>
//#include <GLBatch.h>
//#include <GLFrame.h>
//#include <GLMatrixStack.h>
//#include <GLGeometryTransform.h>
//#include <StopWatch.h>
//
//#include <math.h>
//#include <stdio.h>
//
//#ifdef __APPLE__
//#include <glut/glut.h>
//#else
//#define FREEGLUT_STATIC
//#include <GL/glut.h>
//#endif
//
//#define NUM_SPHERES 50
//GLFrame spheres[NUM_SPHERES];
//
//GLShaderManager shaderManager;
//GLFrustum viewFrustum;
//GLTriangleBatch torusBatch;
//GLBatch floorBatch;
//GLGeometryTransform transformPipline;
//
//GLMatrixStack modelViewMatrix;
//GLMatrixStack projectionMatrix;
//GLFrame cameraFrame;
//
//
//void ChangeSize(int w, int h) {
//    glViewport(0, 0, w, h);
//    
//    viewFrustum.SetPerspective(35.0f, float(w)/float(h), 1, 500);
//    projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
//    
//    modelViewMatrix.LoadIdentity();
//    transformPipline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
//}
//
//void RenderScene() {
//    static GLfloat vFLoorColor[] = {0.0f, 1.f, 0.f, 1,0};
//    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
//    
//    shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipline.GetModelViewMatrix(), vFLoorColor);
//    floorBatch.Draw();
//    glutSwapBuffers();
//}
//
//void SpecialKeys(int key, int x, int y) {
//    
//}
//
//void SetupRC() {
//    glClearColor(0.3, 0.3, 0.3, 1);
//    glEnable(GL_DEPTH_TEST);
//    shaderManager.InitializeStockShaders();
//    
//    floorBatch.Begin(GL_LINES, 324);
//    for(GLfloat x = -20; x <= 20; x+=0.5f) {
//        floorBatch.Vertex3f(x, -0.55f, -20);
//        floorBatch.Vertex3f(x, -0.55f, 20);
//        
//        floorBatch.Vertex3f(-20, -0.5f, x);
//        floorBatch.Vertex3f(20, -0.5f, x);
//    }
//    floorBatch.End();
//}
//
//int main(int argc, char* argv[]) {
//    gltSetWorkingDirectory(argv[0]);
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB);
//    glutInitWindowSize(800,600);
//    glutCreateWindow("公转自转");
//    glutReshapeFunc(ChangeSize);
//    glutDisplayFunc(RenderScene);
//    glutSpecialFunc(SpecialKeys);
//    
//    GLenum err = glewInit();
//    if(err != GLEW_OK) {
//        fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
//        return 1;
//    }
//    SetupRC();
//    glutMainLoop();
//    return 0;
//}
