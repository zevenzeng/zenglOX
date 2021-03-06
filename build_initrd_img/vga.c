// vga.c -- 测试vga图形界面

#include "common.h"
#include "syscall.h"
#include "vga.h"
#include "task.h"

//Byte array of bitmap of 64 x 64 px:
		
UINT8 mono_img [] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xC7, 0xFF, 0xFC, 0x00, 0x1D, 0xC0, 
	0x1F, 0xFF, 0xC7, 0xFF, 0xFC, 0x1F, 0x1D, 0xD8, 0x1C, 0x01, 0xC0, 0x00, 0x7C, 0x1F, 0x1D, 0xD8, 
	0x1D, 0xFD, 0xC1, 0xDD, 0xFF, 0x7F, 0xDD, 0xF8, 0x1D, 0xFD, 0xC1, 0xDD, 0xF7, 0x71, 0xDC, 0x70, 
	0x1D, 0xFD, 0xC7, 0xFD, 0xF7, 0xFF, 0xFF, 0xF0, 0x1D, 0xFD, 0xC7, 0x71, 0xF1, 0xFF, 0x77, 0xF0, 
	0x1D, 0xFD, 0xC7, 0xF1, 0xF1, 0xFF, 0xFF, 0xF0, 0x1D, 0xFD, 0xC7, 0xF0, 0x01, 0xFF, 0xFC, 0x70, 
	0x1D, 0xFD, 0xDF, 0xF7, 0xDF, 0xFF, 0xFF, 0x78, 0x1C, 0x01, 0xDF, 0xC7, 0xDF, 0x7C, 0x1F, 0x18, 
	0x1F, 0xFF, 0xDF, 0xF7, 0xDF, 0x7D, 0xDF, 0x18, 0x1F, 0xFF, 0xC7, 0x71, 0xDF, 0x7D, 0xDC, 0x00, 
	0x1F, 0xFF, 0xDF, 0xF1, 0xFF, 0x7D, 0xDF, 0xC0, 0x00, 0x00, 0x1F, 0xC0, 0x77, 0x7C, 0x1F, 0xC0, 
	0x07, 0xDF, 0xDF, 0xDF, 0x7F, 0xFF, 0xFF, 0xC0, 0x07, 0xDF, 0xDD, 0xDF, 0x1D, 0xFF, 0xFD, 0xC0, 
	0x07, 0xDF, 0xFF, 0xDF, 0xDD, 0xFF, 0xFF, 0xC0, 0x07, 0x00, 0x7F, 0x07, 0xC1, 0xFF, 0xF7, 0x00, 
	0x07, 0xC7, 0xFF, 0xC7, 0xF7, 0xFF, 0xF7, 0x18, 0x01, 0xC7, 0xFD, 0xC7, 0xF7, 0x1C, 0x70, 0x18, 
	0x07, 0xC7, 0xFD, 0xFF, 0xFF, 0x1D, 0xFF, 0x18, 0x07, 0xC7, 0x71, 0xFC, 0x1C, 0x1D, 0xFF, 0x18, 
	0x1F, 0xDF, 0xFD, 0xFC, 0x7C, 0x1D, 0xFF, 0xD8, 0x1C, 0x1D, 0xFD, 0xC0, 0x7C, 0x00, 0x07, 0xC0, 
	0x1F, 0x1F, 0xFD, 0xF1, 0xFF, 0xF7, 0x07, 0xF8, 0x07, 0x07, 0x00, 0x71, 0xDF, 0xF7, 0x07, 0xF8, 
	0x07, 0xFF, 0xF0, 0x71, 0xDF, 0xFF, 0xC7, 0xF8, 0x01, 0xFD, 0xF0, 0x71, 0xDF, 0xDD, 0xC0, 0x00, 
	0x01, 0xFF, 0xF7, 0xFD, 0xDF, 0xFD, 0xDF, 0x18, 0x00, 0x77, 0x07, 0xDD, 0xC0, 0x7D, 0xDF, 0x18, 
	0x1D, 0xF7, 0xF7, 0xDF, 0xDF, 0xFF, 0xFF, 0x78, 0x1D, 0xF1, 0xF7, 0xC7, 0xDF, 0xF7, 0xF7, 0x70, 
	0x1F, 0xF1, 0xFF, 0xFF, 0xFF, 0xF7, 0xFF, 0x70, 0x07, 0xF0, 0x1F, 0x7F, 0xFF, 0xC7, 0xDF, 0x00, 
	0x07, 0xF1, 0xDF, 0xFF, 0xFF, 0xDF, 0xFF, 0xC0, 0x07, 0x71, 0xDD, 0xF7, 0xC0, 0x1D, 0xF1, 0xC0, 
	0x07, 0xF1, 0xDF, 0xF7, 0xFF, 0x1D, 0xFF, 0xF0, 0x01, 0xC0, 0x07, 0xC0, 0x7F, 0x1C, 0x7F, 0x70, 
	0x01, 0xC7, 0xC7, 0xF7, 0x7F, 0xDD, 0xFF, 0xF8, 0x00, 0x07, 0xC0, 0x77, 0x01, 0xDD, 0xDD, 0xD8, 
	0x00, 0x07, 0xDD, 0xFF, 0x71, 0xFD, 0xDD, 0xD8, 0x00, 0x00, 0x1D, 0xFC, 0x70, 0x7C, 0x00, 0x00, 
	0x1F, 0xFF, 0xDD, 0xFD, 0xFD, 0xFD, 0xFF, 0xF8, 0x1F, 0xFF, 0xDD, 0xDD, 0xDD, 0xDD, 0xFF, 0xF8, 
	0x1F, 0xFF, 0xDF, 0xFD, 0xFD, 0xDD, 0xFF, 0xF8, 0x1C, 0x01, 0xC7, 0x7C, 0x7D, 0xDD, 0xC0, 0x18, 
	0x1D, 0xFD, 0xDF, 0x7F, 0xFD, 0xFD, 0xDF, 0xD8, 0x1D, 0xFD, 0xDF, 0x7F, 0xF0, 0x71, 0xDF, 0xD8, 
	0x1D, 0xFD, 0xDF, 0x7F, 0xF7, 0x7D, 0xDF, 0xD8, 0x1D, 0xFD, 0xC0, 0x07, 0x07, 0x7D, 0xDF, 0xD8, 
	0x1D, 0xFD, 0xDF, 0xF7, 0xFF, 0xFD, 0xDF, 0xD8, 0x1D, 0xFD, 0xDF, 0xF1, 0xFD, 0xFD, 0xDF, 0xD8, 
	0x1D, 0xFD, 0xDF, 0xF7, 0xFF, 0xFD, 0xDF, 0xD8, 0x1C, 0x01, 0xC7, 0xC7, 0xF7, 0x71, 0xC0, 0x18, 
	0x1F, 0xFF, 0xDF, 0xDF, 0xFF, 0xF1, 0xFF, 0xF8, 0x1F, 0xFF, 0xDF, 0x1F, 0xDD, 0xF1, 0xFF, 0xF8, 
	0x1F, 0xFF, 0xDF, 0x1F, 0xDD, 0xF1, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

UINT8 * vga_8x16_font = 0;

UINT32 vga_mode;

int plot_pixel(UINT8 * buffer ,int x, int y, UINT8 c)
{
	int wd_in_bytes;
	int off;

	if(vga_mode == VGA_MODE_320X200X256)
	{
		wd_in_bytes = 320;
		off = wd_in_bytes * y + x;
		buffer[off] = c;
	}
	else if(vga_mode == VGA_MODE_640X480X16)
	{
		int pmask, p, plane_size = (640 * 480) / 8;
		UINT8 mask;
		wd_in_bytes = 640 / 8;
		off = wd_in_bytes * y + x / 8;
		x = (x & 7) * 1;
		mask = 0x80;
		asm volatile ("shrb %%cl, %%al" :"=a"(mask):"c"(x),"0"(mask));
		//mask = 0x80 >> x;
		pmask = 1;
		for(p = 0; p < 4; p++)
		{
			if(pmask & c)
				buffer[off] |=  mask;
			else
				buffer[off] &=  ~mask;
			pmask <<= 1;
			buffer += plane_size;
		}
	}
	return 0;
}

int draw_mono_img(UINT8 * buffer, UINT8 * img, int color, int x, int y, int w, int h)
{
	int c,d,i,j,z, wc = w / 8;
	for(c = (h - 1),d=0;c >= 0;c--,d++)
	{
		UINT8 * tmp_img = img + wc * c;
		for(i=0;i < wc;i++)
			for(j = 7,z = 0;j >= 0;j--,z++)
				if(tmp_img[i] & (1 << j))
					plot_pixel(buffer, x + z + i * 8, y + d, (UINT8)color);
	}
	return 0;
}

int draw_char(UINT8 * buffer, char ch, int color, int x, int y)
{
	UINT8 * tmp_font = vga_8x16_font + ((int)ch) * 16;
	int i,j,z;
	for(i=0;i < 16;i++)
		for(j = 7,z = 0;j >= 0;j--,z++)
			if(tmp_font[i] & (1 << j))
				plot_pixel(buffer, x + z, y + i, (UINT8)color);
	return 0;
}

int draw_string(UINT8 * buffer, char * str, int color, int x, int y)
{
	int i;
	for(i=0;str[i] != '\0';i++)
		draw_char(buffer, str[i], color, x + i * 8, y);
	return 0;
}

int draw_rect(UINT8 * buffer, int color, int x, int y, int w, int h)
{
	int wd_in_bytes;
	int off, i;

	if(vga_mode == VGA_MODE_320X200X256)
	{
		wd_in_bytes = 320;
		for(i=0;i < h;i++)
		{
			off = wd_in_bytes * (y + i) + x;
			memset((buffer + off), (UINT8)color, w);
		}
	}
	else if(vga_mode == VGA_MODE_640X480X16)
	{
		//int j;
		//for(i = 0;i < h;i++)
		//	for(j=0;j < w;j++)
		//		plot_pixel(buffer , x + j,  y + i, color);

		int p, s, e, n, m, plane_size = (640 * 480) / 8, pmask, x_in_bytes;
		UINT8 extra;
		s = x % 8;
		e = (w >= 8) ? 0 : (8 - s - w) ;
		n = (w - (8 - s - e)) / 8;
		m = (w - (8 - s - e)) % 8;
		wd_in_bytes = 640 / 8;
		x_in_bytes = x / 8;
		pmask = 1;
		for(p=0;p < 4;p++)
		{
			for(i=0;i < h;i++)
			{
				off = wd_in_bytes * (y + i) + x_in_bytes;
				if(pmask & color)
				{
					extra = 0xff;
					asm volatile ("shrb %%cl, %%al" :"=a"(extra):"c"(s),"0"(extra));
					extra &= (0xff << e);
					buffer[off] |= extra;
					memset((buffer + off + 1), 0xff, n);
					if(m > 0)
					{
						extra = 0x80;
						asm volatile ("sarb %%cl, %%al" :"=a"(extra):"c"(m-1),"0"(extra));
						buffer[off + 1 + n] |= extra;
					}
				}
				else
				{
					extra = 0xff;
					asm volatile ("shrb %%cl, %%al" :"=a"(extra):"c"(s),"0"(extra));
					extra &= (0xff << e);
					buffer[off] &= ~extra;
					memset((buffer + off + 1), 0x0, n);
					if(m > 0)
					{
						extra = 0x80;
						asm volatile ("sarb %%cl, %%al" :"=a"(extra):"c"(m-1),"0"(extra));
						buffer[off + 1 + n] &= ~extra;
					}
				}
			}
			pmask <<= 1;
			buffer += plane_size;
		}
	}
	return 0;
}

int main(VOID * task, int argc, char * argv[])
{
	UNUSED(argc);
	UNUSED(argv);
	
	syscall_cmd_window_write("you can't use vga in this version! because we are in vbe mode.");
	return 0;

	if(argc == 2 && strcmp(argv[1],"mouse") == 0)
	{
		vga_mode = VGA_MODE_640X480X16;
		vga_8x16_font = (UINT8 *)syscall_vga_get_text_font();
		syscall_vga_set_mode(vga_mode);
		UINT8 * buffer;
		UINT32 buf_size;
		if(vga_mode == VGA_MODE_320X200X256)
		{
			buf_size = 320 * 200;
			buffer = (UINT8 *)syscall_umalloc(buf_size);
		}
		else
		{
			buf_size = ((640 * 480) / 8) * 4;
			buffer = (UINT8 *)syscall_umalloc(buf_size);
		}
		if(vga_mode == VGA_MODE_320X200X256)
			memset(buffer, 13, 320 * 200);
		else if(vga_mode == VGA_MODE_640X480X16)
			draw_rect(buffer, 13, 0, 0, 640, 480);
		draw_rect(buffer, 8, 10, 10, 15, 15);
		syscall_vga_update_screen(buffer, buf_size);
		syscall_set_input_focus(task);
		TASK_MSG msg;
		int ret, x = 10,y = 10;
		while(TRUE)
		{
			ret = syscall_get_tskmsg(task,&msg,TRUE);
			if(ret != 1)
			{
				syscall_idle_cpu();
				continue;
			}
			if(msg.type == MT_KEYBOARD && 
				msg.keyboard.type == MKT_ASCII && 
				msg.keyboard.ascii == 0x1B) // ESC
				break;
			if(msg.type != MT_MOUSE)
				continue;
			/*if(msg.mouse.rel_x > 10)
				msg.mouse.rel_x = 10;
			else if(msg.mouse.rel_x < -10)
				msg.mouse.rel_x = -10;
			if(msg.mouse.rel_y > 10)
				msg.mouse.rel_y = 10;
			else if(msg.mouse.rel_y < -10)
				msg.mouse.rel_y = -10;*/
			x += msg.mouse.rel_x;
			y -= msg.mouse.rel_y;
			y = (y < 10) ? 10 : y;
			y = ((y+15) > 450) ? (450 - 15) : y;
			x = (x < 10) ? 10 : x;
			x = ((x + 10) > 600) ? (600 - 10) : x;
			if(vga_mode == VGA_MODE_320X200X256)
				memset(buffer, 13, 320 * 200);
			else if(vga_mode == VGA_MODE_640X480X16)
				draw_rect(buffer, 13, 0, 0, 640, 480);
			draw_rect(buffer, 8, x, y, 15, 15);
			syscall_vga_update_screen(buffer, buf_size);
		}
		syscall_ufree(buffer);
		syscall_vga_set_mode(VGA_MODE_80X25_TEXT);
		return 0;
	}

	if(argc == 2)
	{
		if(strcmp(argv[1],"640") == 0)
			vga_mode = VGA_MODE_640X480X16;
		else
		{
			syscall_monitor_write("usage: vga [640]");
			return -1;
		}
	}
	else
	{
		vga_mode = VGA_MODE_320X200X256;
	}
	vga_8x16_font = (UINT8 *)syscall_vga_get_text_font();
	syscall_vga_set_mode(vga_mode);
	UINT8 * buffer;
	UINT32 buf_size;
	if(vga_mode == VGA_MODE_320X200X256)
	{
		buf_size = 320 * 200;
		buffer = (UINT8 *)syscall_umalloc(buf_size);
	}
	else
	{
		buf_size = ((640 * 480) / 8) * 4;
		buffer = (UINT8 *)syscall_umalloc(buf_size);
	}
	if(vga_mode == VGA_MODE_320X200X256)
		memset(buffer, 13, 320 * 200);
	else if(vga_mode == VGA_MODE_640X480X16)
		draw_rect(buffer, 13, 0, 0, 640, 480);
	draw_rect(buffer, 8, 10, 10, 300, 180);
	draw_rect(buffer, 14, 15, 15, 290, 170);
	draw_string(buffer, "hello world, press ESC to Exit", 0, 25, 25);
	draw_string(buffer, "up,down,left,right key to move", 0, 25, 45);
	draw_string(buffer, "the qrcode image is www.zengl.com", 0, 25, 65);
	draw_mono_img(buffer, mono_img, 0, 25, 85, 64, 64);
	syscall_vga_update_screen(buffer, buf_size);
	syscall_set_input_focus(task);
	TASK_MSG msg;
	int ret, x = 25,y = 85, flag = 0;
	while(TRUE)
	{
		ret = syscall_get_tskmsg(task,&msg,TRUE);
		if(ret != 1)
		{
			syscall_idle_cpu();
			continue;
		}
		if(msg.type != MT_KEYBOARD)
			continue;
		if(msg.keyboard.type == MKT_ASCII && 
			msg.keyboard.ascii == 0x1B) // ESC
				break;
		else if(msg.keyboard.type == MKT_KEY)
		{
			switch(msg.keyboard.key)
			{
			case MKK_CURSOR_UP_PRESS:
				y-=5;
				flag = 1;
				break;
			case MKK_CURSOR_DOWN_PRESS:
				y+=5;
				flag = 1;
				break;
			case MKK_CURSOR_LEFT_PRESS:
				x-=5;
				flag = 1;
				break;
			case MKK_CURSOR_RIGHT_PRESS:
				x+=5;
				flag = 1;
				break;
			default:
				flag = 0;
				break;
			}
			if(flag)
			{
				y = (y < 85) ? 85 : y;
				y = ((y+64) > 185) ? (185 - 64) : y;
				x = (x < 15) ? 15 : x;
				x = ((x + 64) > 305) ? (305 - 64) : x;
				draw_rect(buffer, 14, 15, 85, 290, 100);
				draw_mono_img(buffer, mono_img, 0, x, y, 64, 64);
				syscall_vga_update_screen(buffer, buf_size);
			}
		}
	}
	syscall_ufree(buffer);
	syscall_vga_set_mode(VGA_MODE_80X25_TEXT);
	return 0;
}

