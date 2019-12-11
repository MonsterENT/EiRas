//
//  ViewController.m
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/11/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#import "ViewController.h"

#import <MetalKit/MetalKit.h>
#import <Metal/Metal.h>
#import <MetalKit/MTKView.h>

#include <GraphicsAPI/EiRas.hpp>
#include <PlatformDependency/OnMetal/GraphicsAPI/EiRasMetal.h>

#include <Material/Material.hpp>
#include <Material/Shader.hpp>
#include <Graphics/CommandBuffer.hpp>
#include <Mesh/Mesh.hpp>

#include <string>
using std::string;
using GraphicsAPI::EiRas;
using namespace MaterialSys;
using Graphics::CommandBuffer;

@interface ViewController()<MTKViewDelegate>
@property(strong, nonatomic)MTKView* mtkView;
@end

@implementation ViewController

GraphicsAPI::EiRas* device = 0;

MaterialSys::Material* mat = 0;

Graphics::CommandBuffer* cmdBuffer = 0;

Mesh* m_mesh = 0;

- (void)viewDidLoad {
    [super viewDidLoad];
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _mtkView = [[MTKView alloc]initWithFrame:self.view.frame device:MTLCreateSystemDefaultDevice()];
        _mtkView.delegate = self;
        [EiRasMetal SetMetalKitView:_mtkView];
        
        device = GraphicsAPI::EiRas::Create();
        // Do any additional setup after loading the view.
        
        cmdBuffer = new Graphics::CommandBuffer("m_cmdBuffer");
        
        mat = new Material("m_mat", new Shader("m_shader", "vertexShader", "fragmentShader"), cmdBuffer);
        
        m_mesh = new Mesh("m_mesh");
        
        [self.view addSubview:_mtkView];
    });
}


#pragma MTKView Delegate
- (void)mtkView:(nonnull MTKView *)view drawableSizeWillChange:(CGSize)size
{
    
}

- (void)drawInMTKView:(nonnull MTKView *)view
{
    device->OnUpdate();
    
    cmdBuffer->BeginFrame();
    cmdBuffer->SetMaterial(mat);
    
    cmdBuffer->DrawMesh(m_mesh);
    cmdBuffer->Commit(true);
}


@end
