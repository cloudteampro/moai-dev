//
//  PreviewViewController.m
//  GSExample
//
//  Created by Giuseppe Perniola on 05/02/2016.
//  Copyright © 2016 GameSparks Technologies Ltd. All rights reserved.
//

#import "PreviewViewController.h"

@interface PreviewViewController ()

@end

@implementation PreviewViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.label = [[UITextField alloc] initWithFrame:[UIScreen mainScreen].bounds];
    self.label.text = @"GameSparks Preview Mode";
    self.label.textColor = [UIColor lightGrayColor];
    [self.label setUserInteractionEnabled:FALSE];
    [self.label setContentVerticalAlignment:UIControlContentVerticalAlignmentBottom];
    [self.view addSubview:self.label];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

- (UIInterfaceOrientationMask)supportedInterfaceOrientations
{
    return UIInterfaceOrientationMaskAll;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return YES;
}

- (BOOL)shouldAutorotate
{
    return YES;
}

- (void)viewWillLayoutSubviews
{
    //self.label.frame = [UIScreen mainScreen].bounds;
    self.label.frame = CGRectMake(0,
               self.view.frame.size.height - 20.0f,
               self.view.frame.size.width,
               20.0f);
}

@end
