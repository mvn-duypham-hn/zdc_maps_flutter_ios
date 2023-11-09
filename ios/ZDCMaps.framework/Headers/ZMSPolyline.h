//
//  ZMSPolyline.h
//  ZDCMaps
//
//  Created by zdc on 2016/01/13.
//  Copyright (c) 2016年 ZENRIN DataCom Co., LTD.. All rights reserved.
//

#import <UIKit/UIkit.h>
#import "ZMSOverlay.h"

@class ZMSPath;

NS_ASSUME_NONNULL_BEGIN

/// ## ポリラインクラス
/// 地図上に線を重畳する。
@interface ZMSPolyline : ZMSOverlay

// MARK: - プロパティー

/// ### パス
/// @note パスの座標が1点以下の場合は設定できない。<br>頂点数は最大16000までで、上限を超えた頂点は描画されない。
@property(nonatomic, copy) ZMSPath *path;

/// ### 線幅
/// @note 有効範囲: 0.0 - 100.0px<br>デフォルト値: 10.0
@property(nonatomic, assign) CGFloat strokeWidth;

/// ### 線色
/// @note デフォルト値: #ffff7fff
@property(nonatomic, strong) UIColor *strokeColor;

// MARK: - メソッド

/// ### パスからZMSPolylineを作成する
/// @note 頂点数は最大16000点。超過した頂点は描画されない。
/// @param path: パス
/// @return ポリライン
+ (nullable instancetype)polylineWithPath:(ZMSPath *)path;

@end

NS_ASSUME_NONNULL_END
