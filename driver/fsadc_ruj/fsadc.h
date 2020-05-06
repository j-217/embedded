#ifndef __FSADC_H
#define __FSADC_H

union chan_val {
    unsigned int chan;
    unsigned int val;
};

#define FSADC_MAGIC 'A'
#define FSADC_GET_VAL _IOWR(FSADC_MAGIC, 0, union chan_val)

#endif