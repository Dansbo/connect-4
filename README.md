# connect-4

March 2 2021:
Today I succeeded in loading the sprites/gamepieces into memory. I created a spriteattrib.bin file, which contains the sprite attributes, which are loaded directly into to the sprite registers of VERA.

I struggled alot to remember how to convert the VERA addres, where the picture is loaded to the address that is used in the sprite registers.

I could vaguely remember that it was something like taking the VERA addres and shifting it by a number of bits either right or left. The issue must be that I never really understood why it was necessary. My brother referred me to the documentation for the VERA and I read it several times.

Finally it dawned on me. The issue is that the address in the sprite registers only considers the top 7 bits of the address.

In binary the hexadecimal address of $0D600 converts to %1101 0110 0000 0000 and when we want to tell VERA, where to fetch the image data for the sprite we can shift the number right 5 times, which will remove the lower five 0, which are unnecessary anyway (though not mathematically)

When shifted the referral address becomes %110 1011 0000 which converts to $06B0 in hexadecimal.

The sprite attributes file was rather easy to make. (I peeked at the file made with the project my brother and I made)

The sprite attribute registers in VERA contains 8 offsets which all can be described with hexadecimal. So for the first sprite the data became:

                        B0 06 00 00 00 00 00 50

Remember the 65c02 is little endian which means it reads address "backwards" why is why the address is flipped. The last byte was calculated as %0101 0000 which converts to $50.
The %0101 defines the size of the sprite to be 16x16 pixels. So I could just copy that line 21 times.

The next address was calculated as follows.

Since the pieces.bin cointains both pieces on top of each other the size of the original picture is 16x32 but we don't want to shop both pieces at a time. So I needed to calculate how space the first piece takes in ram.

I have made use of only the first 16 colors in the CX16 palette (C64 palette) so this means that picture is 4 bpp.
So the calculation becomes 16x16x4 = 1024 bits. Which equals 1024/8 = 128 bytes. This converts to $80 which has to be added to the startaddress of the picture $D600 + $80 = $D680. So the referral address is $D680>>5 = $06B4

So then I added 21 new entries as above but just switching the first B0 out with B4.

Before finishing up the spriteattrib.bin file I inserted $00 00 in the beginning, as I believe the LOAD kernal routine uses the first two bytes as address. Which I am not using in my case.

As I tested the first sprite by just enabling it I noticed that the "holes" in my gameboard picture aren't aligned, so I need to create a new picture.

The data of spriteattrib.bin is loaded to Bank 1 $FC08 as I believe the first sprite register is used by the mousepointer, which I hope to use later.
____________________________________________________________________________________________________

February 28 2021:
I succeeded by getting the board loaded to the screen using old routines and macros from the project X-shots I had with my brother.

I have also loaded the pieces that I figure I will be using sprites to move around.

My first obstacle will be to make the sprites appear on the top of the screen and then I figure the user can use the arrow keys and the return bottom to move the piece and release it down the column.

As the game has 6 rows by 7 columns I figure that in order to fill all the spaces there should be 42 game pieces in total an thus 21 per player.

The only instance I can figure there would be a draw is if all spaces are filled up and no one has four pieces in a row.

After that I need to have some bytes set aside to store the information of where there are pieces so that the computer at a later time can figure out if anyone has won the game.

____________________________________________________________________________________________________

February 27 2021:
I am realizing that starting from scratch is a bit of a test for myself. I can only blame myself as I have put this off for way to long.

My brother has been kind enough to help me. I cannot comprehend how frustrating this must be for him, as he also helped me a lot in the beginning. Almost a year ago. Lesson learned! I need to keep on programming to keep my knowledge up.

I have created the "board" for the game in piskel as well as the binaries for the player pieces.

I am thinking that I will keep this game rather simple and develop the AI in the same fashion as I did for tictactoe. And I'm thinking that maybe this game would benefit from mouse control as well.

Maybe I will start out just programming that the user can pick a "column" using the number keys. But I think it would be cool to also being able to use the mouse to point and click. But let's see how far I'll get with this.

At the moment it seems that I have been able to conjure up a way to load the board into the VERA videoram but somehow I missed how to enable the picture that I have just loaded. So I will need to go back to the documentation. (Maybe I should stop cheating by using my brothers inc file and code the stuff myself)

Anyways this is how far I got today.

____________________________________________________________________________________________________

February 26 2021:
This will be a project to try and revitalize my enthusiasm with assembly programming for the Commander X16.

I thought to myself that I had already created tictactoe for the platform.

I am thinking this project should be rather easy to accomplish.

This readme file will be updated as I go along and I will try to document the process
