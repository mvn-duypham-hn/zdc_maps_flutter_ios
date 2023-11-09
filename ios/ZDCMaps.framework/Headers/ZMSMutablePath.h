//
//  ZMSMutablePath.h
//  ZDCMaps
//
//  Created by zdc on 2016/01/29.
//  Copyright (c) 2016年 ZENRIN DataCom Co., LTD.. All rights reserved.
//

#import "ZMSPath.h"

NS_ASSUME_NONNULL_BEGIN

/// ## ミュータブルパスクラス
/// 座標の配列を保持するクラス。<br>`ZMSPolygon` や `ZMSPolyline` で使用する。<br>生成後も点列の変更が可能。
/// @note 不正な値を含む点列でポリゴンを生成した場合は動作を保証しない。
@interface ZMSMutablePath : ZMSPath

// MARK: - メソッド

/// ### 新規の座標をパスの末尾に追加する
/// @param coord: 座標 (緯度/経度)
- (void)addCoordinate:(CLLocationCoordinate2D)coord;

/// ### 新規の座標をパスの末尾に追加する
/// @param latitude: 緯度
/// @param longitude: 経度
- (void)addLatitude:(CLLocationDegrees)latitude longitude:(CLLocationDegrees)longitude;

/// ### 指定したインデックスに座標を挿入する
/// @param coord: 座標 (緯度/経度)
/// @param index: インデックス
- (void)insertCoordinate:(CLLocationCoordinate2D)coord atIndex:(NSUInteger)index;

/// ### 指定したインデックスを指定した座標で置き換える
/// @param index: インデックス
/// @param coord: 座標(緯度/経度)
- (void)replaceCoordinateAtIndex:(NSUInteger)index withCoordinate:(CLLocationCoordinate2D)coord;

/// ### 指定したインデックスの座標を削除する
/// @param index: インデックス
- (void)removeCoordinateAtIndex:(NSUInteger)index;

/// ### 末尾の座標を削除する
- (void)removeLastCoordinate;

/// ### 全ての座標を削除する
- (void)removeAllCoordinates;

@end

NS_ASSUME_NONNULL_END
