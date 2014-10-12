#ifndef __UI_BREAKPOINT_H__
#define __UI_BREAKPOINT_H__

#include "common.h"

#define INT3_CODE 0xcc
#define WP BP
typedef struct breakpoint {
	int NO;
	struct breakpoint *next;

	/* TODO: Add more members if necessary */
	int count;

	swaddr_t addr;
	uint8_t code,tmp;

	char expr[100];
	uint32_t value;

} BP;

BP* new_bp();
bool free_bp(BP* bp);
void set_bp(BP* bp);
void reset_bp(BP* bp);
BP* get_bp(swaddr_t addr);

WP* new_wp();
bool free_wp(WP* wp);
bool check_wp();

void delete_all();
void delete_bp(int NO);

void hide_bp();
void show_bp();
#endif
