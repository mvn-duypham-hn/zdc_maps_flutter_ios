//
//  ZMSPath.h
//  ZDCMaps
//
//  Created by zdc on 2014/12/08.
//  Copyright (c) 2014年 ZENRIN DataCom Co., LTD.. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>

NS_ASSUME_NONNULL_BEGIN

/// ## パスクラス
/// 座標の配列を保持するクラス。<br>`ZMSPolygon` や `ZMSPolyline` で使用する。<br>生成後の点列の変更は不可。
/// @note 不正な値を含む点列でポリゴンを生成した場合は動作を保証しない。
@interface ZMSPath : NSObject<NSCopying, NSMutableCopying>

// MARK: - メソッド

/// ### 座標が空のZMSPathを生成する
/// @return パス
+ (instancetype)path;

/// ### 別のパスを指定するZMSPathのイニシャライザー
/// @param path: パス
- (instancetype)initWithPath:(ZMSPath *)path;

/// ### 含まれる座標の数を取得する
/// @return 含まれる座標の数
- (NSInteger)count;

/// ### 任意のインデックスの座標を取得する
/// @param index: インデックス
/// @return 座標(緯度/経度)
- (CLLocationCoordinate2D)coordinateAtIndex:(NSInteger)index;

@end

NS_ASSUME_NONNULL_END
