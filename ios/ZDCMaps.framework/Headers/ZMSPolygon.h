//
//  ZMSPolygon.h
//  ZDCMaps
//
//  Created by zdc on 2016/01/13.
//  Copyright (c) 2016年 ZENRIN DataCom Co., LTD.. All rights reserved.
//

#import <UIKit/UIkit.h>
#import "ZMSOverlay.h"

@class ZMSPath;

NS_ASSUME_NONNULL_BEGIN

/// ## ポリゴンクラス
/// 地図上にポリゴンを重畳する。
@interface ZMSPolygon : ZMSOverlay

// MARK: - プロパティー

/// ### パス
/// @note パスの座標が2点以下の場合は設定できない。<br>頂点数は最大16000までで、上限を超えた場合正常に描画されない。
@property(nonatomic, copy) ZMSPath *path;

/// ### 線幅
/// @note 有効範囲: 0.0 - 100.0px<br>デフォルト値: 5.0
@property(nonatomic, assign) CGFloat strokeWidth;

/// ### 線色
/// @note デフォルト値: #000000ff
@property(nonatomic, strong) UIColor *strokeColor;

/// ### 塗りつぶし色
/// @note デフォルト値: #ffffffff
@property(nonatomic, strong) UIColor *fillColor;

/// ### 穴のパス
/// ポリゴンに穴を空ける際に利用する。
/// @note パスは複数設定可能。
@property(nonatomic, strong) NSArray<ZMSPath *> *holes;

// MARK: - メソッド

/// ### パスからZMSPolygonを作成する
/// @warning パスの座標が2点以下の場合はnilが戻る。
/// @param path: パス
/// @return ポリゴン
+ (nullable instancetype)polygonWithPath:(ZMSPath *)path;

@end

NS_ASSUME_NONNULL_END
