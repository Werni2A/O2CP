# Test Documentation

Parsing an unknown binary file format is an erroneous task. It is easy to break working functionality with future changes. For this reason, unit tests are an essential component in the development process for such a parser. However, creating test cases for all scenarios in all possible file format versions is practically not feasible. As a result, a different approach is taken that is described in the following as black box unit testing.

## Black Box Unit Tests

Unit tests are typically white box tests where everything is known about the test, such that it's easy to compare own results against the unit test. Here a different approach is taken by using unknown open source designs as black box unit tests. We do not know anything about the design that is used but feed it into our parser. The parser will fail on some files with unimplemented features but will also pass on some correctly parsed files. The number of failures is saved in a database. When changes to the parser's source code are applied another run against the black box designs is initiated. In case the number of errors is reduced, we improved the parser a little bit. In case the number of errors is increased, we know that we introduced a regression. With this technique it is possible to run unit tests against hundreds of open source designs, consequently improving coverage of our unit tests. This works well because one design is an archive that contains multiple files where we get more precise error feedback. I.e. a symbol library file (`*.OLB`) contains 100 symbols where 43 fail and 57 pass. Then the 43 failures will be saved in the database `repos.yaml`. When the parser is modified at a later point in time and the test is run again we know that at most 43 files are allowed to fail because the other symbols passed in an earlier parser revision. I.e. a regression was introduced.

## Adding new Test Files

**This is not correct anymore - Needs to be rewritten**

The general workflow is shown in the following:

1. Add new repository to `repos.yaml` and preset the error counter to a very high value (`99999`)
2. Clone Git Repository
3. Generate unit tests that check the number of failures as described above
4. Unit tests generate a log file containing the number of failures in the current run
5. Check whether fewer failures than previously showed up, then the parser was improved. As a result, reduce the error counter in `repos.yaml` accordingly

The whole test suite will take more than 1 hour to run, better grab a coffee. If you are only interested in the test result 'pass' or 'fail' reduce the parsers verbosity. Otherwise log files of greater than 15 GB will be generated.
