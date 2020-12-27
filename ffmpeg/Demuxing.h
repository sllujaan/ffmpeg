#pragma once

#include<iostream>



/**
 * @file
 * libavformat demuxing API use example.
 *
 * Show how to use the libavformat and libavcodec API to demux and
 * decode audio and video data.
 * @example doc/examples/demuxing.c
 */
extern "C" {
#include <libavutil/imgutils.h>
#include <libavutil/samplefmt.h>
#include <libavutil/timestamp.h>
#include <libavformat/avformat.h>

}

static AVFormatContext* fmt_ctx = NULL;
static AVCodecContext* video_dec_ctx = NULL, * audio_dec_ctx;
static AVStream* video_stream = NULL, * audio_stream = NULL;
static const char* src_filename = NULL;
static const char* video_dst_filename = NULL;
static const char* audio_dst_filename = NULL;
static FILE* video_dst_file = NULL;
static FILE* audio_dst_file = NULL;
static uint8_t* video_dst_data[4] = { NULL };
static int      video_dst_linesize[4];
static int video_dst_bufsize;
static uint8_t** audio_dst_data = NULL;
static int       audio_dst_linesize;
static int audio_dst_bufsize;
static int video_stream_idx = -1, audio_stream_idx = -1;
static AVFrame* frame = NULL;
static AVPacket pkt;
static int video_frame_count = 0;
static int audio_frame_count = 0;




static int open_codec_context(int* stream_idx,
    AVFormatContext* fmt_ctx, enum AVMediaType type)
{
    int ret;
    AVStream* st;
    AVCodecContext* dec_ctx = NULL;
    AVCodec* dec = NULL;
    ret = av_find_best_stream(fmt_ctx, type, -1, -1, NULL, 0);
    if (ret < 0) {
        fprintf(stderr, "Could not find %s stream in input file '%s'\n",
            av_get_media_type_string(type), src_filename);
        return ret;
    }
    else {
        *stream_idx = ret;
        st = fmt_ctx->streams[*stream_idx];
        /* find decoder for the stream */
        dec_ctx = st->codec;
        dec_ctx = (AVCodecContext*)st->codecpar;
        dec = avcodec_find_decoder(dec_ctx->codec_id);
        if (!dec) {
            fprintf(stderr, "Failed to find %s codec\n",
                av_get_media_type_string(type));
            return ret;
        }
        if ((ret = avcodec_open2(dec_ctx, dec, NULL)) < 0) {
            fprintf(stderr, "Failed to open %s codec\n",
                av_get_media_type_string(type));
            return ret;
        }
    }

    return 0;
}
















int initDumxing(int argc, char** argv) {

    int ret = 0, got_frame = 0;
    if (argc != 4) {
        fprintf(stderr, "usage: %s input_file video_output_file audio_output_file\n"
            "API example program to show how to read frames from an input file.\n"
            "This program reads frames from a file, decodes them, and writes decoded\n"
            "video frames to a rawvideo file named video_output_file, and decoded\n"
            "audio frames to a rawaudio file named audio_output_file.\n"
            "\n", argv[0]);
        return 1;
    }


    src_filename = argv[1];
    video_dst_filename = argv[2];
    audio_dst_filename = argv[3];

    /* register all formats and codecs */
    //av_register_all();

    /* open input file, and allocate format context */
    if (avformat_open_input(&fmt_ctx, src_filename, NULL, NULL) < 0) {
        fprintf(stderr, "Could not open source file %s\n", src_filename);
        return 1;
    }

    /* retrieve stream information */
    if (avformat_find_stream_info(fmt_ctx, NULL) < 0) {
        fprintf(stderr, "Could not find stream information\n");
        return 1;
    }

    if (open_codec_context(&video_stream_idx, fmt_ctx, AVMEDIA_TYPE_VIDEO) >= 0) {
        video_stream = fmt_ctx->streams[video_stream_idx];
        video_dec_ctx = video_stream->codec;
        video_dst_file = fopen(video_dst_filename, "wb");
        if (!video_dst_file) {
            fprintf(stderr, "Could not open destination file %s\n", video_dst_filename);
            ret = 1;
            goto end;
        }
        /* allocate image where the decoded image will be put */
        ret = av_image_alloc(video_dst_data, video_dst_linesize,
            video_dec_ctx->width, video_dec_ctx->height,
            video_dec_ctx->pix_fmt, 1);
        if (ret < 0) {
            fprintf(stderr, "Could not allocate raw video buffer\n");
            goto end;
        }
        video_dst_bufsize = ret;
    }




    end:
        if (video_dec_ctx)
            avcodec_close(video_dec_ctx);
        if (audio_dec_ctx)
            avcodec_close(audio_dec_ctx);
        avformat_close_input(&fmt_ctx);
        if (video_dst_file)
            fclose(video_dst_file);
        if (audio_dst_file)
            fclose(audio_dst_file);
        av_free(frame);
        av_free(video_dst_data[0]);
        av_free(audio_dst_data);

	return 0;
}