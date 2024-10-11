1. What are the trade offs between using UTF-32 or UTF-8
    I imagine that using UTF-32 would be faster since the indexing would be static
    and also easier on the programmer since they wouldn't need to worry about chars
    of differying bit lengths. However, that would certainly come at the cost of a 
    higher memory overhead since UTF-32 uses 4 byte chars for all chars, even for 
    ASCII characters. So both the file size and memory usage would be up to 4 times 
    larger using UTF-32 rather than UTF-8. UTF-8 has also been used for a very long 
    time so, its going to be EVERYWHERE. That would mean if your program ever interacted
    with other programs that utilized UTF-8 instead of UTF-32, you would need a way to 
    convert from one to the other seemlessly. 

2. What are some trade off of the leading 10 on coniuation bytes?
    While it does take up additional space that could be utilized for more bits, I think
    that the leading 10 allows you to easily distiguish Utf-8 chars from ASCII and makes
    continuation bytes to be instantly identifiable. I have to believe that its removal 
    could also lead to some security issues which C already has plenty of as is when handled
    incorrectly. In conclusion, removing the leading 10 would complicate decoding, increase
    the likelyhood of errors, and potentially pose a security risk. 