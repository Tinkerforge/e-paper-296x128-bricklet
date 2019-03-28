Imports System
Imports Tinkerforge

Module ExampleHelloWorld
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XYZ" ' Change XYZ to the UID of your E-Paper 296x128 Bricklet

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim ep As New BrickletEPaper296x128(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Use black background
        ep.FillDisplay(BrickletEPaper296x128.COLOR_BLACK)

        ' Write big white "Hello World" in the middle of the screen
        ep.DrawText(16, 48, BrickletEPaper296x128.FONT_24X32, _
                    BrickletEPaper296x128.COLOR_WHITE, _
                    BrickletEPaper296x128.ORIENTATION_HORIZONTAL, "Hello World")
        ep.Draw()

        Console.WriteLine("Press key to exit")
        Console.ReadLine()
        ipcon.Disconnect()
    End Sub
End Module
