/** PSP helper library ***************************************/
/**                                                         **/
/**                          font.c                         **/
/**                                                         **/
/** This file contains font manipulation routines           **/
/**                                                         **/
/** Copyright (C) Akop Karapetyan 2007                      **/
/**     You are not allowed to distribute this software     **/
/**     commercially. Please, notify me, if you make any    **/
/**     changes to this file.                               **/
/*************************************************************/
#include "font.h"
#include "stockfont.h"

int pspFontGetLineHeight(const PspFont *font)
{
  return font->Height;
}

int pspFontGetTextWidth(const PspFont *font, const char *string)
{
  const unsigned char *ch;
  int width, max, w;

  for (ch = (unsigned char*)string, width = 0, max = 0; *ch; ch++)
  {
    /* Tab = 4 spaces (TODO) */
    if (*ch == '\t') w = font->Chars[(unsigned char)' '].Width * 4; 
    /* Newline */
    else if (*ch == '\n') width = w = 0;
    /* Special char */
    else if (*ch < 32) w = 0; 
    /* Normal char */
    else w = font->Chars[(unsigned char)(*ch)].Width;

    width += w;
    if (width > max) max = width;
  }

  return max;
}

int pspFontGetTextHeight(const PspFont *font, const char *string)
{
  const char *ch;
  int lines;

  for (ch = string, lines = 1; *ch; ch++)
    if (*ch == '\n') lines++;

  return lines * font->Height;
}

