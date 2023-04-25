using UnityEngine;

public class Piece : MonoBehaviour
{
    public enum PieceType
    {
        King,
        Queen,
        Rook,
        Bishop,
        Knight,
        Pawn
    }

    public bool isWhite;
    public PieceType pieceType;
    public bool hasMoved;
    public Vector2Int currentSquare;
}
