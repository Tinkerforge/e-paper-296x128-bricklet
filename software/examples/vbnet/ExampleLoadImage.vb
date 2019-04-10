Imports System
Imports System.Drawing
Imports System.Threading
Imports Tinkerforge

' Tested with 
' > vbnc /reference:System.Drawing.dll /target:exe /out:Example.exe /reference:Tinkerforge.dll ExampleLoadImage.vb

Module ExampleScribble
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XYZ" ' Change XYZ to the UID of your E-Paper 296x128 Bricklet
    Const WIDTH As Integer = 296
    Const HEIGHT As Integer = 128

	' Convert VB.NET Bitmap to matching color boolean array
    Function BoolArrayFromImage(ByVal bitmap As Bitmap, ByVal color As Color) As Boolean()
        Dim pixels() As Boolean = New Boolean(HEIGHT*WIDTH) {}

        For row As Integer = 0 To HEIGHT - 1
            For column As Integer = 0 To WIDTH - 1
				Dim c As Color =  bitmap.GetPixel(column, row)
				pixels(row*WIDTH + column) = ((c.R = color.R) And (c.G = color.G) And (c.B = color.B))
            Next column
        Next row

		Return pixels
    End Function

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim epaper As New BrickletEPaper296x128(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

		' Download example image here:
		' https://raw.githubusercontent.com/Tinkerforge/e-paper-296x128-bricklet/master/software/examples/tf_red.png
        Dim bitmap As New Bitmap("tf_red.png")

		' Get black/white pixels from image and write them to the Bricklet buffer
		Dim pixelsBW() As Boolean = BoolArrayFromImage(bitmap, Color.White)
		epaper.WriteBlackWhite(0, 0, WIDTH-1, HEIGHT-1, pixelsBW)

		' Get red pixels from image and write them to the Bricklet buffer
		Dim pixelsRed() As Boolean = BoolArrayFromImage(bitmap, Color.Red)
		epaper.WriteColor(0, 0, WIDTH-1, HEIGHT-1, pixelsRed)

		' Draw buffered values to the display
		epaper.Draw()


        Console.WriteLine("Press enter to exit")
        Console.ReadLine()
        ipcon.Disconnect()
    End Sub
End Module
