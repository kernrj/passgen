Passgen generates cryptographically secure passwords.

Running passgen with no arguments produces a 25-character password containing upper and lower case letters, numbers and special characters.

To generate a password with specific requirements, `--alpha`, `--numeric`, `--alphanumeric`, `--special`, and `--extra` can be used.

`--length N` generates a password which is N characters long.

`--upper` generates upper-case letters.

`--lower` generates lower-case letters.

`--alpha` Password will contain both upper- and lower-case letters.

`--numeric` generates numbers (0-9).

`--alphanumeric` generates both letters and numbers.

`--special` generates special characters: \`~!@#$%^&*()_+-=[]\{}|;':",./<>?

`--extra CUSTOM_CHARACTERS` uses the custom characters. For example, `--extra '@$%'` will generate use `@`, `$`, and `%` when generating random characters.

`--max-repeat` Limit the number of repeated characters which are allowed. True random character sequences will contain repeats on occasion, but some password filters prohibit repeats.

Example:

`passgen --alphanumeric --extra '!@#$%' --length 20` generates a 20-character password containing letters, numbers, and at least one of the special characters specified.

Passgen ensures all character classes are represented in the password at least once.

The following classes exist:
- Upper-case letters
- Lower-case letters
- Numbers
- Built-in special characters (see `--special`)
- User-specified extra characters

Options are additive, so specifying `--alpha --numeric` is equivalent to `--alphanumeric`.
