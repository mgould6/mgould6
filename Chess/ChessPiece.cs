using ChessGame;
using System;
using Chess;

public enum PieceType
{
    Pawn,
    Knight,
    Bishop,
    Rook,
    Queen,
    King
}

public enum PieceColor
{
    White,
    Black
}

public class ChessPiece
{
    public PieceType Type { get; set; }
    public PieceColor Color { get; set; }
    public ChessLocation Location { get; set; }

    public ChessPiece(PieceType type, PieceColor color, ChessLocation location)
    {
        Type = type;
        Color = color;
        Location = location;
    }

    public bool IsValidMove(ChessLocation destination)
    {
        // TODO: Implement this method to check if the move is valid for the piece
        throw new NotImplementedException();
    }

    public void Move(ChessLocation destination)
    {
        // TODO: Implement this method to move the piece to the destination location
        throw new NotImplementedException();
    }
}
