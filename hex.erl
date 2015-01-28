-module(hex).

-compile(export_all).

-export([ aes_cfb128/0
        , blowfish/0
        , rc4/0
        ]).

-export([ hex/1 ]).

aes_cfb128() ->
    K = hexstr2bin("61626364656667686162636465666768"),
    I = hexstr2bin("31323334353637386162636465666768"),
    T = hexstr2bin("3132333435363738313233343536373831323334353637383132333435363738"),
    hex(crypto:block_encrypt(aes_cfb128, K, I, T)).

blowfish() ->
    K = hexstr2bin("0123456789abcdeff0e1d2c3b4a5968700000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    I = hexstr2bin("FEDCBA9876543210"),
    T = hexstr2bin("37363534333231204E6F77206973207468652074696D6520666F7220"),
    hex(crypto:block_encrypt(blowfish_cfb64, K, I, T)).

rc4() ->
    K = hexstr2bin("0123456789ABCDEFF0E1D2C3B4A59687"),
    T = hexstr2bin("37363534333231204E6F77206973207468652074696D6520666F722000000000"),
    State = crypto:stream_init(rc4, K),
    {_NewState, CipherText} = crypto:stream_encrypt(State, T),
    hex(CipherText).

hex(Bin) ->
    list_to_binary(lists:flatten(string:join([io_lib:format("~.16B", [X]) || <<X>> <= Bin], ":"))).

hexstr2bin(S) ->
    list_to_binary(hexstr2list(S)).

hexstr2list([X,Y|T]) ->
    [mkint(X)*16 + mkint(Y) | hexstr2list(T)];
hexstr2list([]) ->
    [].

mkint(C) when $0 =< C, C =< $9 ->
    C - $0;
mkint(C) when $A =< C, C =< $F ->
    C - $A + 10;
mkint(C) when $a =< C, C =< $f ->
    C - $a + 10.
