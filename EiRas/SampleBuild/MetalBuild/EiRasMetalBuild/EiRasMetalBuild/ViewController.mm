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
#include <Material/ShaderLayout.h>
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

Material* mat = 0;

ShaderLayout* layout = 0;

Shader* shader = 0;

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
        
        cmdBuffer = new Graphics::CommandBuffer("m_cmdBuffer");
        
        layout = new ShaderLayout();
        layout->SlotNum = 1;
        layout->Slots = new ShaderSlot*[1];
        
        ShaderProp* tmpCBV = new ShaderProp();
        tmpCBV->PropName = "TMP_CBV";
        tmpCBV->PropType = GraphicsResourceType::CBV;
        tmpCBV->BufferSize = sizeof(float) * 4;
        layout->Slots[0] = tmpCBV;
        
        shader = new Shader("m_shader", "vertexShader", "fragmentShader");
        shader->InitLayout(layout);
        
        mat = new Material("m_mat", shader, cmdBuffer);
        static vector_float4 testColor;
        testColor.x = 1;
        testColor.y = 1;
        testColor.z = 0;
        testColor.a = 1;
        mat->SetProperty(0, &testColor);
        
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
    cmdBuffer->Reset();
    cmdBuffer->SetMaterial(mat);
    
    cmdBuffer->DrawMesh(m_mesh);
    cmdBuffer->Commit(true);
}


@end
