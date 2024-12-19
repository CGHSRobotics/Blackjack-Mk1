
#include "lvgl.hpp"


static lv_obj_t* label;

static void slider_event_cb(lv_event_t* e)
{
	lv_obj_t* slider = lv_event_get_target(e);

	/*Refresh the text*/
	lv_label_set_text_fmt(label, "%"LV_PRId32, lv_slider_get_value(slider));
	lv_obj_align_to(label, slider, LV_ALIGN_OUT_TOP_MID, 0, -15);    /*Align top of the slider*/
}

/**
 * Create a slider and write its value on a label.
 */
void lv_example_get_started_3(void)
{
	lv_obj_t* label2 = lv_label_create(lv_scr_act());
	lv_label_set_long_mode(label2, LV_LABEL_LONG_SCROLL_CIRCULAR);     /*Circular scroll*/
	lv_obj_set_width(label2, 150);
	lv_label_set_text(label2, "code worky");
	lv_obj_align(label2, LV_ALIGN_CENTER, 0, 40);
}


void lv_gen_test(void) {

	label = lv_label_create(lv_scr_act());
	lv_label_set_text(label, "Starting gen");
}

void lv_gen_test2(void) {

	label = lv_label_create(lv_scr_act());
	lv_label_set_text(label, "ended gen");
}