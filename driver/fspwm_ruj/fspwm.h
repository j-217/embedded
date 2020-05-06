#pragma once

#define FSPWM_MAGIC 'P'
#define FSPWM_START _IO(FSPWM_MAGIC, 1)
#define FSPWM_STOP _IO(FSPWM_MAGIC, 2)
#define FSPWM_SET_FREQ _IOW(FSPWM_MAGIC, 3, int)