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
#include "Engine.hpp"
#include <PlatformDependency/OnMetal/GraphicsAPI/EiRasMetal.h>
#include <string>
using std::string;

@interface ViewController()<MTKViewDelegate>
@property(strong, nonatomic)MTKView* mtkView;
@end

@implementation ViewController

Engine* engine = 0;

- (void)viewDidLoad {
    [super viewDidLoad];
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _mtkView = [[MTKView alloc]initWithFrame:self.view.frame device:MTLCreateSystemDefaultDevice()];
        _mtkView.delegate = self;
        [EiRasMetal SetMetalKitView:_mtkView];
        [self.view addSubview:_mtkView];
        engine = new Engine();
        engine->InitEngine();
    });
}


#pragma MTKView Delegate
- (void)mtkView:(nonnull MTKView *)view drawableSizeWillChange:(CGSize)size
{
    
}

- (void)drawInMTKView:(nonnull MTKView *)view
{
    engine->Update();
}


@end
