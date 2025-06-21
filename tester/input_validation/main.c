#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "minishell.h"

void	run_test(const char *input)
{
	printf("Testing: [%s]\n", input);
	if (check_syntax_error(input))
		printf("✅ Passed\n\n");
	else
		printf("❌ Syntax error detected\n\n");
}

int	main(void)
{
	run_test("echo 'hello world'");             // OK
	run_test("echo \"hello | world\"");         // OK
	run_test("echo 'hello");                    // unclosed quote
	run_test("cat < infile > outfile");         // OK
	run_test("cat < > outfile");                // invalid redirection
	run_test("ls | grep foo");                  // OK
	run_test("ls || grep foo");                 // invalid operator
	run_test("| ls");                           // invalid operator
	run_test("<< 1 << 2 << 3 << 4 << 5 | << 6 << 7 << 8 << 9 << 10 << 11 << 12 << 13 << 14 << 15 << 16 | << 17");                               // OK (empty input)
	run_test("ls |");                           // invalid operator
	run_test("ls | ");                          // invalid operator
	run_test("cat << EOF");                     // OK (simple case)
	run_test("cat << EOF\"\"");                     // OK (simple case)
	run_test("cat <");                          // invalid redirection
	run_test("echo \"unclosed");                // unclosed quote
	run_test("ls >| grep");                     // invalid redirection (>| not handled)
	run_test("");                               // OK (empty input)

	return 0;
}
