#ifndef PIMEMEDIAPLAYER_H
#define PIMEMEDIAPLAYER_H

#include "stdint.h"
#include "stdbool.h"

typedef struct RegionRect_
{
	double top, left, right, bottom;
} RegionRect;

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef _WIN32
    #if defined(SELF_PIPLAYER_DLL)
        #define ILIVE_PLAYER_EXPORT __declspec(dllexport)
    #else
        #define ILIVE_PLAYER_EXPORT __declspec(dllimport)
    #endif
#else
    #define ILIVE_PLAYER_EXPORT __attribute ((visibility("default")))
#endif


ILIVE_PLAYER_EXPORT void			iLive_Player_global_init_audioplayback_usb_port(const char * usb_port);
ILIVE_PLAYER_EXPORT void			PIMediaPlayer_global_init_audioplayback_usb_port(const char * usb_port);
ILIVE_PLAYER_EXPORT const char	   *iLive_Player_audioplayback_usb_port();
ILIVE_PLAYER_EXPORT const char	   *PIMediaPlayer_audioplayback_usb_port();
ILIVE_PLAYER_EXPORT void            iLive_Player_global_init(const char *);
ILIVE_PLAYER_EXPORT void            PIMediaPlayer_global_init(const char *);
ILIVE_PLAYER_EXPORT const char     *iLive_Player_version();
ILIVE_PLAYER_EXPORT const char     *PIMediaPlayer_version();
ILIVE_PLAYER_EXPORT void*           iLive_Player_create(void* arg, void **view_ptr);
ILIVE_PLAYER_EXPORT void*           PIMediaPlayer_create(void* arg, void **view_ptr);
ILIVE_PLAYER_EXPORT void*           iLive_Player_create_with_config(const char *config);
ILIVE_PLAYER_EXPORT void*           PIMediaPlayer_create_with_config(const char *config);
ILIVE_PLAYER_EXPORT void*           iLive_Player_create_with_psdemux(int stream_id, void *group_id);
ILIVE_PLAYER_EXPORT void*           PIMediaPlayer_create_with_psdemux(int stream_id, void *group_id);
ILIVE_PLAYER_EXPORT void*           iLive_Player_create_PIOptions(int pzsp, void *options);
ILIVE_PLAYER_EXPORT void*           PIMediaPlayer_create_PIOptions(int pzsp, void *options);
ILIVE_PLAYER_EXPORT void*           iLive_Player_create_with_psdemux_PIOptions(int stream_id, void *group_id, void *options);
ILIVE_PLAYER_EXPORT void*           PIMediaPlayer_create_with_psdemux_PIOptions(int stream_id, void *group_id, void *options);
ILIVE_PLAYER_EXPORT void            iLive_Player_dec_ref(void*mp);
ILIVE_PLAYER_EXPORT void            PIMediaPlayer_dec_ref(void*mp);
ILIVE_PLAYER_EXPORT void            iLive_Player_dec_ref_p(void*pmp);
ILIVE_PLAYER_EXPORT void            PIMediaPlayer_dec_ref_p(void*pmp);
ILIVE_PLAYER_EXPORT int             iLive_Player_ps_init_mode(void *mp, int mode, const char *ctx);
ILIVE_PLAYER_EXPORT int             PIMediaPlayer_ps_init_mode(void *mp, int mode, const char *ctx);
ILIVE_PLAYER_EXPORT int             iLive_Player_set_hwnd(void*mp, void*hwnd);
ILIVE_PLAYER_EXPORT int             PIMediaPlayer_set_hwnd(void*mp, void*hwnd);
ILIVE_PLAYER_EXPORT int             iLive_Player_set_hwnd_list_with_rect(void* mp, int list_size, void* hwnd_list, double* left, double *top, double *right, double *bottom);
ILIVE_PLAYER_EXPORT int             PIMediaPlayer_set_hwnd_list_with_rect(void* mp, int list_size, void* hwnd_list, double* left, double *top, double *right, double *bottom);
ILIVE_PLAYER_EXPORT int             iLive_Player_set_hwnd_with_rect(void*mp, void*hwnd, int x, int y, int w, int h);
ILIVE_PLAYER_EXPORT int             PIMediaPlayer_set_hwnd_with_rect(void*mp, void*hwnd, int x, int y, int w, int h);
ILIVE_PLAYER_EXPORT void            iLive_Player_set_option(void *mp, int opt_category, const char *name, const char *value);
ILIVE_PLAYER_EXPORT void            PIMediaPlayer_set_option(void *mp, int opt_category, const char *name, const char *value);
ILIVE_PLAYER_EXPORT void            iLive_Player_set_option_int(void *mp, int opt_category, const char *name, int64_t value);
ILIVE_PLAYER_EXPORT void            PIMediaPlayer_set_option_int(void *mp, int opt_category, const char *name, int64_t value);
ILIVE_PLAYER_EXPORT int             iLive_Player_set_feature(void *mp, int feature_id, bool enable);
ILIVE_PLAYER_EXPORT int             PIMediaPlayer_set_feature(void *mp, int feature_id, bool enable);
ILIVE_PLAYER_EXPORT void            iLive_Player_set_playback_rate(void *mp, float rate);
ILIVE_PLAYER_EXPORT void            PIMediaPlayer_set_playback_rate(void *mp, float rate);
ILIVE_PLAYER_EXPORT void            iLive_Player_set_playback_volume(void *mp, float volume);
ILIVE_PLAYER_EXPORT void            PIMediaPlayer_set_playback_volume(void *mp, float volume);
ILIVE_PLAYER_EXPORT void            iLive_Player_shutdown(void *mp, void *view);
ILIVE_PLAYER_EXPORT void            PIMediaPlayer_shutdown(void *mp, void *view);
ILIVE_PLAYER_EXPORT int             iLive_Player_set_options(void *mp, void *option);
ILIVE_PLAYER_EXPORT int             PIMediaPlayer_set_options(void *mp, void *option);
ILIVE_PLAYER_EXPORT int             iLive_Player_apply_expect_state(void *mp);
ILIVE_PLAYER_EXPORT int             PIMediaPlayer_apply_expect_state(void *mp);
ILIVE_PLAYER_EXPORT int             iLive_Player_set_data_source(void *mp, void *view, const char *url);
ILIVE_PLAYER_EXPORT int             PIMediaPlayer_set_data_source(void *mp, void *view, const char *url);
ILIVE_PLAYER_EXPORT int             iLive_Player_prepare_async(void *mp);
ILIVE_PLAYER_EXPORT int             PIMediaPlayer_prepare_async(void *mp);
ILIVE_PLAYER_EXPORT int             iLive_Player_start(void *mp);
ILIVE_PLAYER_EXPORT int             PIMediaPlayer_start(void *mp);
ILIVE_PLAYER_EXPORT int             iLive_Player_pause(void *mp);
ILIVE_PLAYER_EXPORT int             PIMediaPlayer_pause(void *mp);
ILIVE_PLAYER_EXPORT int             iLive_Player_stop(void *mp);
ILIVE_PLAYER_EXPORT int             PIMediaPlayer_stop(void *mp);
ILIVE_PLAYER_EXPORT int             iLive_Player_seek_to(void *mp, long msec);
ILIVE_PLAYER_EXPORT int             PIMediaPlayer_seek_to(void *mp, long msec);
ILIVE_PLAYER_EXPORT bool            iLive_Player_is_playing(const void *mp);
ILIVE_PLAYER_EXPORT bool            PIMediaPlayer_is_playing(const void *mp);
ILIVE_PLAYER_EXPORT int64_t         iLive_Player_get_current_position(void *mp);
ILIVE_PLAYER_EXPORT int64_t         PIMediaPlayer_get_current_position(void *mp);
ILIVE_PLAYER_EXPORT int64_t         iLive_Player_get_duration(void *mp);
ILIVE_PLAYER_EXPORT int64_t         PIMediaPlayer_get_duration(void *mp);
ILIVE_PLAYER_EXPORT int             iLive_Player_set_video_buffering_threshold(void *mp, int threshold);
ILIVE_PLAYER_EXPORT int             PIMediaPlayer_set_video_buffering_threshold(void *mp, int threshold);
ILIVE_PLAYER_EXPORT bool            iLive_Player_open_d3d11();
ILIVE_PLAYER_EXPORT bool            PIMediaPlayer_open_d3d11();
ILIVE_PLAYER_EXPORT void*           iLive_Player_create_union_render(void *hwnd, int w, int h);
ILIVE_PLAYER_EXPORT void*           PIMediaPlayer_create_union_render(void *hwnd, int w, int h);
ILIVE_PLAYER_EXPORT void            iLive_Player_destroy_union_render(void *renderer);
ILIVE_PLAYER_EXPORT void            PIMediaPlayer_destroy_union_render(void *renderer);
ILIVE_PLAYER_EXPORT int             iLive_Player_start_union_render(void *renderer);
ILIVE_PLAYER_EXPORT int             PIMediaPlayer_start_union_render(void *renderer);
ILIVE_PLAYER_EXPORT int             iLive_Player_stop_union_render(void *renderer);
ILIVE_PLAYER_EXPORT int             PIMediaPlayer_stop_union_render(void *renderer);
ILIVE_PLAYER_EXPORT int             PIMediaPlayer_add_to_union_render(void *mp, void *renderer, int x, int y, int w, int h);

#define ILIVE_PLAYER_OP_ID_GET_VIEW_NUMBER               1
#define PIMEDIAPLAYER_OP_ID_GET_VIEW_NUMBER               1
#define ILIVE_PLAYER_OP_ID_GET_AUDIO_NUMBER              2
#define PIMEDIAPLAYER_OP_ID_GET_AUDIO_NUMBER              2
#define ILIVE_PLAYER_OP_ID_SET_AUDIO                     3
#define PIMEDIAPLAYER_OP_ID_SET_AUDIO                     3
#define ILIVE_PLAYER_OP_ID_GET_BITRATE_NUMBER            4
#define PIMEDIAPLAYER_OP_ID_GET_BITRATE_NUMBER            4
#define ILIVE_PLAYER_OP_ID_SET_BITRATE                   5
#define PIMEDIAPLAYER_OP_ID_SET_BITRATE                   5
#define ILIVE_PLAYER_OP_ID_GET_ADAPTIVE                  6
#define PIMEDIAPLAYER_OP_ID_GET_ADAPTIVE                  6
#define ILIVE_PLAYER_OP_ID_PS_AUDIO_MUTE                 7
#define PIMEDIAPLAYER_OP_ID_PS_AUDIO_MUTE                 7
#define ILIVE_PLAYER_OP_ID_PS_SET_MODE                   8
#define PIMEDIAPLAYER_OP_ID_PS_SET_MODE                   8
#define ILIVE_PLAYER_OP_ID_SET_BACK_GROUND               9
#define PIMEDIAPLAYER_OP_ID_SET_BACK_GROUND               9
#define ILIVE_PLAYER_OP_ID_GET_EXTRATS                   10
#define PIMEDIAPLAYER_OP_ID_GET_EXTRATS                   10
#define ILIVE_PLAYER_OP_ID_PS_RECONNECT                  11
#define PIMEDIAPLAYER_OP_ID_PS_RECONNECT                  11
#define ILIVE_PLAYER_OP_ID_PS_STREAM_CTRL                12
#define PIMEDIAPLAYER_OP_ID_PS_STREAM_CTRL                12
#define ILIVE_PLAYER_OP_ID_PS_GET_TIME_STAMP             13
#define PIMEDIAPLAYER_OP_ID_PS_GET_TIME_STAMP             13
#define ILIVE_PLAYER_OP_ID_PS_SWITCH_BITRATE_CALLBACK    14
#define PIMEDIAPLAYER_OP_ID_PS_SWITCH_BITRATE_CALLBACK    14
#define ILIVE_PLAYER_OP_ID_PS_SWITCH_VOLUME_CHANGE_CALLBACK   15
#define PIMEDIAPLAYER_OP_ID_PS_SWITCH_VOLUME_CHANGE_CALLBACK   15
#define ILIVE_PLAYER_OP_ID_PS_FORCE_AUDIO_OPEN_WITH_PARAMETERS 16
#define PIMEDIAPLAYER_OP_ID_PS_FORCE_AUDIO_OPEN_WITH_PARAMETERS 16
#define ILIVE_PLAYER_OP_ID_PS_GET_VIEW_NAME              17
#define PIMEDIAPLAYER_OP_ID_PS_GET_VIEW_NAME              17
#define ILIVE_PLAYER_OP_ID_PS_GET_NODE_IP                18
#define PIMEDIAPLAYER_OP_ID_PS_GET_NODE_IP                18
#define ILIVE_PLAYER_OP_ID_PS_GET_CURRENT_VIEW_NAME      19
#define PIMEDIAPLAYER_OP_ID_PS_GET_CURRENT_VIEW_NAME      19
#define ILIVE_PLAYER_OP_ID_PS_GET_AUDIO_NAME             20
#define PIMEDIAPLAYER_OP_ID_PS_GET_AUDIO_NAME             20
#define ILIVE_PLAYER_OP_ID_PS_GET_CURRENT_AUDIO_NAME     21
#define PIMEDIAPLAYER_OP_ID_PS_GET_CURRENT_AUDIO_NAME     21
#define ILIVE_PLAYER_OP_ID_RECORD_AUDIO_DATA             22
#define PIMEDIAPLAYER_OP_ID_RECORD_AUDIO_DATA             22
#define ILIVE_PLAYER_OP_ID_PS_SET_VIEW                   23
#define PIMEDIAPLAYER_OP_ID_PS_SET_VIEW                   23
#define ILIVE_PLAYER_OP_ID_PS_SET_VIEW2                  24
#define PIMEDIAPLAYER_OP_ID_PS_SET_VIEW2                  24
#define ILIVE_PLAYER_OP_ID_UPDATE_PZBINFO                25
#define PIMEDIAPLAYER_OP_ID_UPDATE_PZBINFO                25
#define ILIVE_PLAYER_OP_ID_PS_GET_BITRATE                26
#define PIMEDIAPLAYER_OP_ID_PS_GET_BITRATE                26
#define ILIVE_PLAYER_OP_ID_PS_GET_CURRENT_BITRATE        27
#define PIMEDIAPLAYER_OP_ID_PS_GET_CURRENT_BITRATE        27
#define ILIVE_PLAYER_OP_ID_PS_GET_NSTEST_CAPS            28
#define PIMEDIAPLAYER_OP_ID_PS_GET_NSTEST_CAPS            28
#define ILIVE_PLAYER_OP_ID_PS_SET_NSTEST_RULES           29
#define PIMEDIAPLAYER_OP_ID_PS_SET_NSTEST_RULES           29
#define ILIVE_PLAYER_OP_ID_PS_FLIP_DISPLAY               30
#define PIMEDIAPLAYER_OP_ID_PS_FLIP_DISPLAY               30
#define ILIVE_PLAYER_OP_ID_PS_US_ENABLE_PLAY             31
#define PIMEDIAPLAYER_OP_ID_PS_US_ENABLE_PLAY             31
#define ILIVE_PLAYER_OP_ID_PS_US_FIX_DELAY               32
#define PIMEDIAPLAYER_OP_ID_PS_US_FIX_DELAY               32
#define ILIVE_PLAYER_OP_ID_PS_US_PLAY_STATE              33
#define PIMEDIAPLAYER_OP_ID_PS_US_PLAY_STATE              33
#define ILIVE_PLAYER_OP_ID_PS_PZVT_DELAY                 34
#define PIMEDIAPLAYER_CFUNF_ID_PS_PZVT_DELAY                 34
#define ILIVE_PLAYER_OP_ID_PS_SET_MASTER_SLAVE_STATE     35
#define PIMEDIAPLAYER_OP_ID_PS_SET_MASTER_SLAVE_STATE     35
#define ILIVE_PLAYER_OP_ID_PS_USER_STRING                36
#define PIMEDIAPLAYER_OP_ID_PS_USER_STRING                36
#define ILIVE_PLAYER_OP_ID_PS_ARRC_TARGET                37
#define PIMEDIAPLAYER_OP_ID_PS_ARRC_TARGET                37
#define ILIVE_PLAYER_OP_ID_PS_STREAM_STATE               38
#define PIMEDIAPLAYER_OP_ID_PS_STREAM_STATE               38
#define ILIVE_PLAYER_OP_ID_PS_FORCE_RECONNECT            39
#define PIMEDIAPLAYER_OP_ID_PS_FORCE_RECONNECT            39
#define ILIVE_PLAYER_OP_ID_PS_RETRY_NOWAIT               40
#define PIMEDIAPLAYER_OP_ID_PS_RETRY_NOWAIT               40
#define ILIVE_PLAYER_OP_ID_PS_UPDATE_PARAM               41
#define PIMEDIAPLAYER_OP_ID_PS_UPDATE_PARAM               41
#define ILIVE_PLAYER_OP_ID_PS_USER_DATA                  42
#define PIMEDIAPLAYER_OP_ID_PS_USER_DATA                  42
#define ILIVE_PLAYER_OP_ID_MP3_MIX                       43
#define PIMEDIAPLAYER_OP_ID_MP3_MIX                       43
#define ILIVE_PLAYER_OP_ID_PS_REQUEST_I                  44
#define PIMEDIAPLAYER_OP_ID_PS_REQUEST_I                  44
#define ILIVE_PLAYER_OP_ID_PS_SET_AVMODE                 45
#define PIMEDIAPLAYER_OP_ID_PS_SET_AVMODE                 45
#define ILIVE_PLAYER_OP_ID_RENDER_CHANGE                 46
#define PIMEDIAPLAYER_OP_ID_RENDER_CHANGE                 46

#define ILIVE_PLAYER_OP_ID_SET_MSG_CALLBACK              201
#define PIMEDIAPLAYER_OP_ID_SET_MSG_CALLBACK              201
#define ILIVE_PLAYER_OP_ID_DEL_MSG_CALLBACK              202
#define PIMEDIAPLAYER_OP_ID_DEL_MSG_CALLBACK              202
#define ILIVE_PLAYER_OP_ID_SET_SCALING_MODE              205
#define PIMEDIAPLAYER_OP_ID_SET_SCALING_MODE              205
#define ILIVE_PLAYER_OP_ID_SET_STREAM_ID_AND_GROUP_ID    207
#define PIMEDIAPLAYER_OP_ID_SET_STREAM_ID_AND_GROUP_ID    207
#define ILIVE_PLAYER_OP_ID_SET_PLAYBACK_RATE             208
#define PIMEDIAPLAYER_OP_ID_SET_PLAYBACK_RATE             208
#define ILIVE_PLAYER_OP_ID_USE_PSDEMUX_RECORD            209
#define PIMEDIAPLAYER_OP_ID_USE_PSDEMUX_RECORD            209
#define ILIVE_PLAYER_OP_ID_SET_MAX_AND_TARGET_DURATION   211
#define PIMEDIAPLAYER_OP_ID_SET_MAX_AND_TARGET_DURATION   211
#define ILIVE_PLAYER_OP_ID_RESET_CONNECT                 212
#define PIMEDIAPLAYER_OP_ID_RESET_CONNECT                 212
#define ILIVE_PLAYER_OP_ID_GET_STREAM_ID                 213
#define PIMEDIAPLAYER_OP_ID_GET_STREAM_ID                 213

/*
    回调函数类型为PI_Audio_Callback
    arg[0] 是否启动音频回调
    arg[1] 回调句柄，会在回调时作为参数
    arg[2] 回调函数指针
*/
#define ILIVE_PLAYER_OP_ID_SET_AUDIO_CALLBACK            214
#define PIMEDIAPLAYER_OP_ID_SET_AUDIO_CALLBACK            214

/*
    回调函数类型为PI_Video_Callback
    Android:
        arg[0] 回调句柄，会在回调时作为参数 ;
		arg[1] 回调函数指针 ;
	    arg[2] 回调数据类型 0: yuv（硬解硬渲染不支持）  1: bitmap;
        Android端回调bitmap数据时，仅opaque和frame为有效数据。
*/
#define ILIVE_PLAYER_OP_ID_SET_VIDEO_CALLBACK            215
#define PIMEDIAPLAYER_OP_ID_SET_VIDEO_CALLBACK            215
#define ILIVE_PLAYER_OP_ID_SET_FEATURE                   216
#define PIMEDIAPLAYER_OP_ID_SET_FEATURE                   216
#define ILIVE_PLAYER_OP_ID_SET_EXTRA_SURFACE_RENDER_VIEW 217
#define PIMEDIAPLAYER_OP_ID_SET_EXTRA_SURFACE_RENDER_VIEW 217
#define ILIVE_PLAYER_OP_ID_SET_RENDER                    218
#define PIMEDIAPLAYER_OP_ID_SET_RENDER                    218
#define ILIVE_PLAYER_OP_ID_GET_SCREEN_SHOT               219
#define PIMEDIAPLAYER_OP_ID_GET_SCREEN_SHOT               219
#define ILIVE_PLAYER_OP_ID_SET_SCHEDULE                  220
#define PIMEDIAPLAYER_OP_ID_SET_SCHEDULE                  220
#define ILIVE_PLAYER_OP_ID_DEL_SCHEDULE                  221
#define PIMEDIAPLAYER_OP_ID_DEL_SCHEDULE                  221
#define ILIVE_PLAYER_OP_ID_GET_SNAPSHOT                  222
#define PIMEDIAPLAYER_OP_ID_GET_SNAPSHOT                  222
#define ILIVE_PLAYER_OP_ID_GET_MPATHUSAGE                223
#define PIMEDIAPLAYER_OP_ID_GET_MPATHUSAGE                223
#define ILIVE_PLAYER_OP_ID_GET_STREAMID                  224
#define PIMEDIAPLAYER_OP_ID_GET_STREAMID                  224
#define ILIVE_PLAYER_OP_ID_GET_PS_OPEN_TIME_INFO         225
#define PIMEDIAPLAYER_OP_ID_GET_PS_OPEN_TIME_INFO         225
#define ILIVE_PLAYER_OP_ID_GET_OPEN_ERROR_CODE           226
#define PIMEDIAPLAYER_OP_ID_GET_OPEN_ERROR_CODE           226
#define ILIVE_PLAYER_OP_ID_RECORD_AUDIO_FILE             227
#define PIMEDIAPLAYER_OP_ID_RECORD_AUDIO_FILE             227
#define ILIVE_PLAYER_OP_ID_GET_BUFFER_PERCENT            228
#define PIMEDIAPLAYER_OP_ID_GET_BUFFER_PERCENT            228
#define ILIVE_PLAYER_OP_ID_PSGLOBAL_REFRESH              229
#define PIMEDIAPLAYER_OP_ID_PSGLOBAL_REFRESH              229
#define ILIVE_PLAYER_OP_ID_SYNC_PLAY                     230
#define PIMEDIAPLAYER_OP_ID_SYNC_PLAY                     230
#define ILIVE_PLAYER_OP_ID_SYNC_PAUSE                    231
#define PIMEDIAPLAYER_OP_ID_SYNC_PAUSE                    231
#define ILIVE_PLAYER_OP_ID_RECV_SYNC_PLAY                232
#define PIMEDIAPLAYER_OP_ID_RECV_SYNC_PLAY                232
#define ILIVE_PLAYER_OP_ID_GET_TRACK_COUNT               233
#define PIMEDIAPLAYER_OP_ID_GET_TRACK_COUNT               233
#define ILIVE_PLAYER_OP_ID_GET_TRACK_TYPE                234
#define PIMEDIAPLAYER_OP_ID_GET_TRACK_TYPE                234
#define ILIVE_PLAYER_OP_ID_SELECT_TRACK                  235
#define PIMEDIAPLAYER_OP_ID_SELECT_TRACK                  235
#define ILIVE_PLAYER_OP_ID_AUDIO_CHANNEL_MIX             236
#define PIMEDIAPLAYER_OP_ID_AUDIO_CHANNEL_MIX             236
#define ILIVE_PLAYER_OP_ID_SYNC_RESUME                   237
#define PIMEDIAPLAYER_OP_ID_SYNC_RESUME                   237
#define ILIVE_PLAYER_OP_ID_SYNC_PAUSE_WITH_PZVT          238
#define PIMEDIAPLAYER_OP_ID_SYNC_PAUSE_WITH_PZVT          238
#define ILIVE_PLAYER_OP_ID_SET_CUSTOMIZED_LIBRARY        239
#define PIMEDIAPLAYER_OP_ID_SET_CUSTOMIZED_LIBRARY        239
#define ILIVE_PLAYER_OP_ID_ADD_SPFILTER_LIBRARY          240
#define PIMEDIAPLAYER_OP_ID_ADD_SPFILTER_LIBRARY          240
#define ILIVE_PLAYER_OP_ID_REMOVE_SPFILTER_LIBRARY       241
#define PIMEDIAPLAYER_OP_ID_REMOVE_SPFILTER_LIBRARY       241
#define ILIVE_PLAYER_OP_ID_SET_VIDEO_CALLBACK_EI         242 /* with extrainfo */
#define PIMEDIAPLAYER_OP_ID_SET_VIDEO_CALLBACK_EI         242 /* with extrainfo */
#define ILIVE_PLAYER_OP_ID_ADD_VPFILTER                  243
#define PIMEDIAPLAYER_OP_ID_ADD_VPFILTER                  243
#define ILIVE_PLAYER_OP_ID_REMOVE_VPFILTER               244
#define PIMEDIAPLAYER_OP_ID_REMOVE_VPFILTER               244
#define ILIVE_PLAYER_OP_ID_SET_AUDIO_CALLBACK_EI         245
#define PIMEDIAPLAYER_OP_ID_SET_AUDIO_CALLBACK_EI         245

#define ILIVE_PLAYER_OP_ID_APPSHARE_ADD_WITH_HOOK        301
#define PIMEDIAPLAYER_OP_ID_APPSHARE_ADD_WITH_HOOK        301
#define ILIVE_PLAYER_OP_ID_APPSHARE_START_INPUT_CAPTURE  302
#define PIMEDIAPLAYER_OP_ID_APPSHARE_START_INPUT_CAPTURE  302
#define ILIVE_PLAYER_OP_ID_APPSHARE_STOP_INPUT_CAPTURE   303
#define PIMEDIAPLAYER_OP_ID_APPSHARE_STOP_INPUT_CAPTURE   303
#define ILIVE_PLAYER_OP_ID_APPSHARE_SET_ID               304
#define PIMEDIAPLAYER_OP_ID_APPSHARE_SET_ID               304


//get something
#define ILIVE_PLAYER_OP_ID_GET_PZVT          1001
#define PIMEDIAPLAYER_OP_ID_GET_PZVT          1001

#define PI_ASPECT_ASPECT_FIT_PARENT                          0
#define PI_ASPECT_ASPECT_FILL_PARENT                         1
#define PI_ASPECT_ASPECT_WRAP_CONTENT                        2
#define PI_ASPECT_MATCH_PARENT                               3
#define PI_ASPECT_16_9_FIT_PARENT                            4
#define PI_ASPECT_4_3_FIT_PARENT                             5
#define PI_ASPECT_FILL_WIDTH_ON_TOP                          6

ILIVE_PLAYER_EXPORT int64_t iLive_Player_set_player_op(void* mp, void *view, int op_id, int op_len, void* op_val, int ret_len, void* ret_val);
ILIVE_PLAYER_EXPORT int64_t PIMediaPlayer_set_player_op(void* mp, void *view, int op_id, int op_len, void* op_val, int ret_len, void* ret_val);
ILIVE_PLAYER_EXPORT int PI_message_loop_n(void *arg);

int psp_aec_callback(void *opaque, uint8_t *stream, int len);
void* PIMediaPlayer_get_ffp(void *mp);
void PIMediaPlayer_stop_drop_audio(void *mp);
void PIMediaPlayer_start_drop_audio(void *mp);

#define VIDEO_CB_YUV     0
#define VIDEO_CB_CV_MAT  1
#define VIDEO_CB_TEXTURE_2D 2

#define VIDEO_CB_ANDROID_BITMAP 1

ILIVE_PLAYER_EXPORT int iLive_Player_set_video_region(void *mp, int index, RegionRect *region);
ILIVE_PLAYER_EXPORT int PIMediaPlayer_set_video_region(void *mp, int index, RegionRect *region);
ILIVE_PLAYER_EXPORT int iLive_Player_AudioConsumer(void *mp, uint32_t *len, float ***wave, uint32_t *channel_cnt);
ILIVE_PLAYER_EXPORT int PIMediaPlayer_AudioConsumer(void *mp, uint32_t *len, float ***wave, uint32_t *channel_cnt);
ILIVE_PLAYER_EXPORT int iLive_Player_AddCustomPlugin(void *plugin);
ILIVE_PLAYER_EXPORT int PIMediaPlayer_AddCustomPlugin(void *plugin);
ILIVE_PLAYER_EXPORT int iLive_Player_vpfilter_preload(void *plugin);
ILIVE_PLAYER_EXPORT int PIMediaPlayer_vpfilter_preload(void *plugin);
ILIVE_PLAYER_EXPORT int iLive_Player_plugincmd(const char *cmd);
ILIVE_PLAYER_EXPORT int PIMediaPlayer_plugincmd(const char *cmd);
ILIVE_PLAYER_EXPORT void *iLive_Player_get_ptr(int channel_no);
ILIVE_PLAYER_EXPORT void *PIMediaPlayer_get_ptr(int channel_no);
ILIVE_PLAYER_EXPORT int iLive_Player_get_channel_no(void *mp);
ILIVE_PLAYER_EXPORT int PIMediaPlayer_get_channel_no(void *mp);
ILIVE_PLAYER_EXPORT int iLive_Player_ModuleCmdWithReturn(const char *cmd_json, char **return_json);
ILIVE_PLAYER_EXPORT int PIMediaPlayer_ModuleCmdWithReturn(const char *cmd_json, char **return_json);
ILIVE_PLAYER_EXPORT int iLive_Player_set_msgstyle(int style); /* 0:iLive, 1:FFPlay, defalut:1 */
ILIVE_PLAYER_EXPORT int PIMediaPlayer_set_msgstyle(int style); /* 0:iLive, 1:FFPlay, defalut:1 */

typedef void (*MsgCb_Type)(int what, int arg1, int arg2, void* extra, void *player);
ILIVE_PLAYER_EXPORT int iLive_SetMsgCb(MsgCb_Type msgcb);
ILIVE_PLAYER_EXPORT void iLive_Player_SendMsg(void *opaque, char* target, unsigned char* data, int size, int flag, int sendlatency, int64_t timestamp);
ILIVE_PLAYER_EXPORT void iLive_Player_GetUrl(void *opaque, char *url, int url_limit);

typedef struct QOEInfo
{
	int16_t ver;
	int64_t venc_avg; /* unit: us */
	int64_t venc_last; /* unit: us */
	uint8_t push_path; /* valid num of pushrtt_xxx and pushretrans_xxx */
	uint8_t recv_path; /* valid num of recvrtt_xxx and recvretrans_xxx */
	int64_t pushrtt_avg[8]; /* unit: us */
	int64_t pushrtt_last[8]; /* unit: us */
	int64_t recvrtt_avg[8]; /* unit: us */
	int64_t recvrtt_last[8]; /* unit: us */
	int32_t pushretrans_avg[8]; /* unit: 0.1% */
	int32_t pushretrans_last[8]; /* unit: 0.1% */
	int32_t recvretrans_avg[8]; /* unit: 0.1% */
	int32_t recvretrans_last[8]; /* unit: 0.1% */
	int64_t pzvtdelay; /* unit: us */
	int64_t vdec; /* unit: us */
	int64_t vbuffer; /* unit: us */
	int64_t abuffer; /* unit: us */
} QOEInfo;

ILIVE_PLAYER_EXPORT void iLive_Player_GetQOE(void *opaque, QOEInfo *ndelta);
ILIVE_PLAYER_EXPORT int iLive_Player_Enum(void **opaque, int mp_limit);
ILIVE_PLAYER_EXPORT int iLive_Player_GetHwnd(void *opaque, void **hwnd, double *left, double *top, double *right, double *bottom, int list_size);



/**
 * @description: 视频数据回调, 若需做耗时工作需copy到其他线程进行处理。
 * @param : opaque 回调句柄
 * @param : frame 视频数据
 * @param : size 视频帧大小
 * @param : stamp 视频时间戳
 * @param : picfmt 视频数据格式
 * @param : width 视频宽度
 * @param : height 视频高度
 * @param : index 拆帧时的索引，
 */
typedef int(*iLive_Player_Video_Callback)(void* opaque, void*frame, int*size, long long stamp, int picfmt, int width, int height, int index);

struct ExtraInfo {
	int64_t orig_timestamp;
};
/**
 * @description: 视频数据回调, 若需做耗时工作需copy到其他线程进行处理。
 * @param : opaque 回调句柄
 * @param : frame 视频数据
 * @param : size 视频帧大小
 * @param : stamp 视频时间戳
 * @param : picfmt 视频数据格式
 * @param : width 视频宽度
 * @param : height 视频高度
 * @param : index 拆帧时的索引
 * @param : extrainfo 帧额外信息
 */
typedef int(*iLive_Player_Video_Callback_EI)(void* opaque, void*frame, int*size, long long stamp, int picfmt, int width, int height, int index, struct ExtraInfo *extrainfo);

/**
 * @description: 音频数据回调，若需做耗时工作需copy到其他线程进行处理。
 * @param : handle 回调句柄
 * @param : sampleRate 采样率
 * @param : channel 声道数
 * @param : samplefmt 格式
 * @param : stamp 时间戳
 * @param : data pcm原始数据
 * @param : data_len 数据长度
 * @param : extrats 无用参数
 */
typedef int(*iLive_Player_Audio_Callback)(void *handle, int sampleRate, int channel, int samplefmt, int64_t stamp, uint8_t *data, int data_len, int64_t extrats);

/**
 * @description: 音频数据回调，若需做耗时工作需copy到其他线程进行处理。
 * @param : handle 回调句柄
 * @param : sampleRate 采样率
 * @param : channel 声道数
 * @param : samplefmt 格式
 * @param : stamp 时间戳
 * @param : data pcm原始数据
 * @param : data_len 数据长度
 * @param : extrats 无用参数
 * @param : extrainfo 帧额外信息
 */
typedef int(*iLive_Player_Audio_Callback_EI)(void *handle, int sampleRate, int channel, int samplefmt, int64_t stamp, uint8_t *data, int data_len, int64_t extrats, struct ExtraInfo *extrainfo);

#ifdef  __cplusplus
}
#endif

#endif
