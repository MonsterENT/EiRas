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
#include <GraphicsAPI/PlatformDependency/Metal/EiRasMetal.h>

@interface ViewController()<MTKViewDelegate>
@property(strong, nonatomic)MTKView* mtkView;
@end

@implementation ViewController

GraphicsAPI::EiRas* device = NULL;

- (void)viewDidLoad {
    [super viewDidLoad];
    
    _mtkView = [[MTKView alloc]initWithFrame:self.view.frame device:MTLCreateSystemDefaultDevice()];
    _mtkView.delegate = self;
    [EiRasMetal SetMetalKitView:_mtkView];
    
    device = GraphicsAPI::EiRas::Create();
    // Do any additional setup after loading the view.
}


#pragma MTKView Delegate
- (void)mtkView:(nonnull MTKView *)view drawableSizeWillChange:(CGSize)size
{
    
}

- (void)drawInMTKView:(nonnull MTKView *)view
{
    device->OnUpdate();
}


@end
