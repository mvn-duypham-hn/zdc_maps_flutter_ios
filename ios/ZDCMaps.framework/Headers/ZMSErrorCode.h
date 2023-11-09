//
//  ZMSErrorCode.h
//  ZDCMaps
//
//  Created by zdc on 2017/01/24.
//  Copyright © 2017年 zdc All rights reserved.
//

/// ## エラーコード
typedef NS_ENUM(int, ZMSErrorCode) {
    /// ### 正常終了
    kZDCMAP_OK = 0,
    /// ### 初期化失敗
    kZDCMAP_FAILED_INIT,
    /// ### 地図の初期化を失敗
    kZDCMAP_FAILED_MAP_INIT,
    /// ### 認証失敗
    kZDCMAP_FAILED_AUTH,
    /// :nodoc:
    kZDCMAP_INCOMPLETE_DRAW = 101
};
