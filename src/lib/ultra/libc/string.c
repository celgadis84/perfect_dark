#include <ultra64.h>

void *memcpy(void *s1, const void *s2, size_t n)
{
	u8 *su1 = (u8 *)s1;
	const u8 *su2 = (const u8 *)s2;

	if (((u32)su1 & 3) == 0 && ((u32)su2 & 3) == 0) {
		u32 *dw = (u32 *)su1;
		const u32 *sw = (const u32 *)su2;
		while (n >= 4) { *dw++ = *sw++; n -= 4; }
		su1 = (u8 *)dw;
		su2 = (const u8 *)sw;
	}

	while (n > 0) {
		*su1++ = *su2++;
		n--;
	}

	return s1;
}

size_t strlen(const char *s)
{
	const char *sc = s;

	while (*sc) {
		sc++;
	}

	return sc - s;
}

char *strchr(const char *s, int c)
{
	const char ch = c;

	while (*s != ch) {
		if (*s == 0) {
			return NULL;
		}

		s++;
	}

	return (char *)s;
}

#ifdef __GNUC__
/**
 * When compiling with gcc it replaces some loops with a call to memset,
 * which means memset must be included in the project.
 */
void *memset(void *str, s32 c, size_t n)
{
	u8 *m1 = (u8 *)str;
	u8 uc = (u8)c;

	if (((u32)m1 & 3) == 0) {
		u32 w = ((u32)uc) | ((u32)uc << 8) | ((u32)uc << 16) | ((u32)uc << 24);
		u32 *dw = (u32 *)m1;
		while (n >= 4) { *dw++ = w; n -= 4; }
		m1 = (u8 *)dw;
	}

	while (n > 0) { *m1++ = uc; n--; }

	return str;
}
#endif
