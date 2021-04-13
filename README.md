# connect-4
April 13, 2021:
Finally I am done moving from the old apartment. Got setup with a new computer and programming environment. So I learned how to compile til X16 Emulator and ROM for myself. So now I should be able to update on my own in the future.

With regards to my programming I have cleaned it up a bit. My brother suggested that I keep all globals in one inc file instead of having them spread all around. This should hopefully make it much easier for me to find them in the future, when I want to look one up.

Tomorrow I need to hand over the old apartment to the owner. Hopefully this can be done without too much of a cost. *Fingers crossed*

I will be busy on Thursday as there is a common workday in the new apartment building, where we have to do some garden work. I am looking forward to get to know my new neighbors. So maybe I can get some coding done Friday.

On Saturday I am going to a summerhouse that we have booked with my in-laws. I plan on bringing my laptop, so that I can code a bit, if I get the time. 
_______________________________________________________________________________

March 18, 2021:

Well there was nothing wrong with the interupt handler that I created. The only issue was, that I was calling my routines every time.

My TextUI routine needs to be called everytime that the player is switched. But that doesn't mean that I need to rewrite the whole routine.

So I think that I will use the Vsync interupt handler, to time, when to move the sprites and such.

Also just now I realize that my brother had already made the same code I did for the interupt handler as a macro in CX16.inc so I didn't need to write my own code, but at least now I know and understand how it works.

My brother suggested that instead of running routines within the interupt handler that I should just use a variable "switch" so my routines know, when they need to be run. That seems like a good idea and I also believe that the code will be more readable.

I think my next project will be to implement a "playtime" counter. My initial thought was to have a counter for each player. But that seems rather unnecessary, as the AI player will always be faster than a human.
_______________________________________________________________________________

March 16, 2021:

Today I've been working with the IRQ Vector for Vertical sync. Kudos to Matt Heffernan (Slithymatt) as I have been watching his episode about interrupts (lesson 10). To create my own IRQ handler.

I can get the custom IRQ handler to work. But when I enable my existing (working) routines the IRQ handler doesn't work.

My initial thought is that it has something to do when I call my routines. But what I don't understand is why my routines get the X16 emulator to crash at a WAI.
_______________________________________________________________________________

March 15, 2021:

I think maybe I had my "Eurika!" moment just now. Of course in the middle where I was making dinner. But I had to go and type down my idea so that I would not forget it.

Instead of doing like I did with tictactoe where I went and defined every single near win. Maybe I could make a small routine to figure out if someone one, or are close to.

Instead of running through every place in the board, maybe I could just have the routine look at the most "interesting" places and then keep a counter of how many a given player have in a row.

So instead of running every place trough sequentially I believe it would be better to run through it sequentially and then run a check. If that check does not match a win then on to the next place and so forth.

Imagine the board like this:

        0       0       0       0       0       0       0
        0       0       0       0       0       0       0
        0       0       B       R       0       0       0
        0       0       R       B       0       0       0
        0       0       B       R       B       0       0
        0       0       R       B       R       B       0

My thought is to loop through one or the other way. First the routine encountes a "Blue" piece it should check in a 3 x 3 area unless it is the lowest row.

Backwards it first encounters a B at row 5 where 0 is the top row. Then I would like the routine to scan sort of like this:

        B       0       0
        R       B       0
        -       -       -

The lowest row of this cut-out does not exist. But the routine could then check one place to the left. That is not a B, så check up-left. Thats a B so then move cut-out to that place and then increment a counter that now there is two in a row. And so forth. When the counter is incremented to 3 there is a win. At 2 there is a near win.

It will never be necessary to check "backwards" as we have already checked that. So let's assume that I check the bytes backwards. My strategy will be as follows.

        X is the counter for the separate bytes
        A zeropage will be the counter for number of connected pieces

        So X is decremented from 41 to 40 in the above example.
        - So we will check the X'th place of the byte and this is a gamepiece.
        - Next step check X-1 to see if that is a matching piece.
        - If not check X-6 too see if that is a matching piece.
        - If not check X-7 to see if that is a matching piece.
        - If not check X-8 to see if that is a matching piece.

        If any of the above steps is a match, then we increment ZP and (push X to the stack) and decrement X as needed and back to the above loop but only check in one direction if ZP>2.
        If none of the above steps or ZP<3 then we just decrement X and check the rest.

I hope this makes sence to any readers out there.

So if I can program the above routine then I think I can handle it without the win scenarios
_______________________________________________________________________________

March 11, 2021:
Today I have spent some time really understanding how to replace the IRQ vector for vertical sync of the VERA as I imagine that I will be using it for my project here.

I have also created a winscenarios.inc where I have listed every single of the possible 69 win scenarios in !byte form.

The thought is that I have now "learned" my program to identify when a player has won. As far as I can calculate that took up 75 bytes of memory just doing that. The strategy I used for tictactoe was to also "learn" the program to identify when someone is close to winning. So I figure i need at least 75 bytes more just to do that. Possibly even more as I could see a problem if the program doesn't know or anticipate a win prior to having connected 3 pieces.

My worries at the moment is that connect-4 is not as simple a game as tictactoe. There are "rules" that define that every single placement below the winning placement needs to be filled up as well.

For instance you can deny the opponent a win by not putting a piece below the winning placement of the opponent and thus either forcing the opponent to drop a game piece into the placement below and allowing you to block their win or start trying to connect 4 pieces in another direction...

So i am wondering if I will at all be able to keep all the code within the memory of the CX16?

Perhaps this game will force me to use the "high" memory area of the CX16....
_______________________________________________________________________________

March 10, 2021:

I have painstakingly recreated my gameboard today. Drawing images takes more time than you think. I also took a couple of tries before I got it right.

But it is done now. The column numbers are hardcoded into the picture and I have added credits.

Also I believe most of the the Text User Interface is done. I have created a small branch that changes the color of the player number to the corresponding color of the gamepiece.

Furthermore I encountered a problem when I tried to look up the color codes for the C64 compatible codes found at:

https://github.com/commanderx16/x16-docs/blob/master/Commander%20X16%20Programmer's%20Reference%20Guide.md#new-control-characters

It didn't work with COLORPORT. But after asking my brother again I was recommended to use the PETSCII color routine insted of COLORPORT. It takes a couple of more lines but hopefully it is more CX16 development secure.

My next step will be to create a gameloop and possibly look into the possibility of emptying the buffer so that the user cannot just press in beforehand what they want to do.

Also I need to get to understand replacing the interrupt handler. I think that maybe I will have the computer keep track of time played in the game.
_______________________________________________________________________________

March 9, 2021:

Today I started trying to make the text userinterface to my game.
My first thought was to number the columns, so it would be more intuitive for the user, how to choose which column they want to drop their piece into.

I created a text string containing all the numbers from 1 to 7. Thinking that it would be easier to just type spaces into the string and then place the numbers using my old Go_XY function. I created the Go_XY function back in the day so that it is more intuitive for me as a programmer, that X defines the horizontal placement of the cursor instead of the native x defining the vertical cursor placement.

Maybe that is just remnants from my time as a math student.

Well, as I got the text to work I realised that I cannot align the cursor placement with my drawing. I also noticed that the "holes" in the board are not aligned. So maybe I should create a new board and just "hard-code" the column numbers into the bitmap.

It is literally back to the drawing board for me.

But atleast most of the "boring" stuff of the game is done being coded. So I expect next time I am updating this readme file that I will have created a new board and got the user interface up and running.
_______________________________________________________________________________

March 2, 2021:
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

February 28, 2021:
I succeeded by getting the board loaded to the screen using old routines and macros from the project X-shots I had with my brother.

I have also loaded the pieces that I figure I will be using sprites to move around.

My first obstacle will be to make the sprites appear on the top of the screen and then I figure the user can use the arrow keys and the return bottom to move the piece and release it down the column.

As the game has 6 rows by 7 columns I figure that in order to fill all the spaces there should be 42 game pieces in total an thus 21 per player.

The only instance I can figure there would be a draw is if all spaces are filled up and no one has four pieces in a row.

After that I need to have some bytes set aside to store the information of where there are pieces so that the computer at a later time can figure out if anyone has won the game.

____________________________________________________________________________________________________

February 27, 2021:
I am realizing that starting from scratch is a bit of a test for myself. I can only blame myself as I have put this off for way to long.

My brother has been kind enough to help me. I cannot comprehend how frustrating this must be for him, as he also helped me a lot in the beginning. Almost a year ago. Lesson learned! I need to keep on programming to keep my knowledge up.

I have created the "board" for the game in piskel as well as the binaries for the player pieces.

I am thinking that I will keep this game rather simple and develop the AI in the same fashion as I did for tictactoe. And I'm thinking that maybe this game would benefit from mouse control as well.

Maybe I will start out just programming that the user can pick a "column" using the number keys. But I think it would be cool to also being able to use the mouse to point and click. But let's see how far I'll get with this.

At the moment it seems that I have been able to conjure up a way to load the board into the VERA videoram but somehow I missed how to enable the picture that I have just loaded. So I will need to go back to the documentation. (Maybe I should stop cheating by using my brothers inc file and code the stuff myself)

Anyways this is how far I got today.

____________________________________________________________________________________________________

February 26, 2021:
This will be a project to try and revitalize my enthusiasm with assembly programming for the Commander X16.

I thought to myself that I had already created tictactoe for the platform.

I am thinking this project should be rather easy to accomplish.

This readme file will be updated as I go along and I will try to document the process
