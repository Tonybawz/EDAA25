#include <stdio.h>
#include "poly.h"

static void poly_test(const char* a, const char* b)
{
	poly_t*		p;
	poly_t*		q;
	poly_t*		r;

	printf("Begin polynomial test of (%s) * (%s)\n", a, b);

	p = new_poly_from_string(a);
	q = new_poly_from_string(b);

	print_poly(p);
	print_poly(q);

	r = mul(p, q);

	print_poly(r);

	free_poly(p);
	free_poly(q);
	free_poly(r);

	printf("End polynomial test of (%s) * (%s)\n", a, b);
}

int main(void)
{
	poly_test("71x^778 - 212x^720 + 531x^674 - 805x^659 + 124x^646 + 982x^576 + 93x^535 + 260x^510 + 799x^450 + 760x^431 - 891x^345 - 748x^275 + 393x^210 + 659x^187 + 723x^120 + 492x^25 - 532x^9 - 908", "-356x^667 - 469x^580 - 360x^556 + 108x^463 - 853x^454 - 864x^422 - 939x^324 - 432x^280 + 316x^221 - 577x^139 - 244x^70 + 882x^8 + 205");
	return 0;
}
