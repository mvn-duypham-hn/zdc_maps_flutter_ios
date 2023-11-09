//
//  ZMSCircle.h
//  ZDCMaps
//
//  Created by zdc on 2016/04/06.
//  Copyright © 2016年 ZENRIN DataCom Co., LTD.. All rights reserved.
//

#import <UIKit/UIkit.h>
#import "ZMSOverlay.h"

NS_ASSUME_NONNULL_BEGIN

/// ## サークルクラス
/// 地図上に円を重畳する。
@interface ZMSCircle : ZMSOverlay

// MARK: - プロパティー

/// ### 座標
/// 表示する位置を指定する。
/// @note 緯度 / 経度
@property(nonatomic, assign) CLLocationCoordinate2D position;

/// ### 半径
/// 円の半径。<br>地図上のメートルで指定する。
/// @warning 0以上である必要がある
@property(nonatomic, assign) CLLocationDistance radius;

/// ### 塗りつぶし色
/// @note デフォルト値: #1919CCCC
@property(nonatomic, strong) UIColor *fillColor;

/// ### 線幅
/// @note 有効範囲: 0.0 - 100.0px<br>デフォルト値: 0
@property(nonatomic, assign) CGFloat strokeWidth;

/// ### 線色
/// @note デフォルト値: #19ff19ff
@property(nonatomic, strong) UIColor *strokeColor;

// MARK: - メソッド

/// ### 座標と半径からZMSCircleを作成する
/// @warning 座標か半径が不正な場合はnilが戻る。
/// @param position: 座標(緯度/経度)
/// @param radius: 半径
/// @return サークル
+ (nullable instancetype)circleWithPosition:(CLLocationCoordinate2D)position radius:(CLLocationDistance)radius;

@end

NS_ASSUME_NONNULL_END
