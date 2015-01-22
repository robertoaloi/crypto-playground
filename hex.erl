-module(hex).

-export([
         test/0
        ]).

test() ->
    Key  = <<"abcdefghabcdefgh">>,
    IV   = <<"12345678abcdefgh">>,
    Text = <<"12345678123456781234567812345678">>,
    print_hex("Key", Key),
    print_hex("Text", Text),
    print_hex("IV", IV),
    Crypt = crypto:block_encrypt(aes_cfb128, Key, IV, Text),
    print_hex("Encrypted", Crypt),
    ok.

print_hex(Title, Bin) ->
    io:format("~s~n", [Title]),
    io:format("~s", [lists:flatten(string:join([io_lib:format("~.16B", [X]) || <<X>> <= Bin], ":"))]),
    io:format("~n").
