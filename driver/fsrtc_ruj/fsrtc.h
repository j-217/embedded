#pragma once

struct rtc_time {
    unsigned int tm_sec;
    unsigned int tm_min;
    unsigned int tm_hour;
    unsigned int tm_day;
    unsigned int tm_mon;
    unsigned int tm_year;
};

#define FSRTC_MAGIC 'R'
#define FSRTC_SET _IOW(FSRTC_MAGIC, 1, struct rtc_time)
#define FSRTC_GET _IOR(FSRTC_MAGIC, 2, struct rtc_time)