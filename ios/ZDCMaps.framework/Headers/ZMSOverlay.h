//
//  ZMSOverlay.h
//  ZDCMaps
//
//  Created by zdc on 2014/12/08.
//  Copyright (c) 2014年 ZENRIN DataCom Co., LTD.. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

@class ZMSMapView;

NS_ASSUME_NONNULL_BEGIN

/// ## 重畳物のベースクラス
/// `ZMSCircle` / `ZMSGroundOverlay` / `ZMSLabel` / `ZMSMarker` / `ZMSPolygon` / `ZMSPolyline` の親クラス
@interface ZMSOverlay : NSObject

// MARK: - プロパティー

/// ### 重畳する地図
/// 初期化した各種重畳物を地図上に表示する際に、対象の地図を設定する。
@property(nonatomic, weak, nullable, setter=setMapValue:) ZMSMapView *map;

/// ### タイトル
/// 重畳物の表示には影響は及ばさず、アプリ側で自由に設定できる。<br>ただし `ZMSMarker` においてはインフォウィンドウ内のテキストとして表示される。
@property(nonatomic, copy, nullable) NSString *title;

/// ### タップイベント
/// このフラグが有効(YES)の場合、重畳物をタップした際にdelegate(`-[ZMSMapViewDelegate mapView:didTapOverlays:]`)が発生する。
/// @note 有効(YES) / 無効(NO)<br>デフォルト値: NO<br>※`ZMSMarker` においてはこのプロパティは機能しない
@property(nonatomic, getter=isTappable) BOOL tappable;

/// ### 重ね順
/// 値が大きい順に地図上に重畳される。
/// @note 値が等しい場合は描画順は未定義となる。<br>デフォルト値: 1<br>※`ZMSMarker` においてはこのプロパティは機能しない
@property(nonatomic) NSInteger zIndex;

/// ### ユーザデータ
/// ユーザーが自由にデータを格納できる。
@property(nonatomic, nullable) id userData;

/// :nodoc:
@property(nonatomic, getter=isVisible) BOOL visible;

/// :nodoc:
@property(nonatomic, readonly) NSString *objectID;

@end

NS_ASSUME_NONNULL_END
