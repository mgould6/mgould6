using System.Collections.Generic;
using UnityEngine;


public class PieceController : MonoBehaviour
{
    public GameObject selectedPiece;
    public LayerMask pieceLayer;
    public bool isWhiteTurn = true;
    public Board board;
    public Piece piece;

    void Update()
    {
        if (Input.GetMouseButtonDown(0))
        {
            RaycastHit2D hit = Physics2D.Raycast(Camera.main.ScreenToWorldPoint(Input.mousePosition), Vector2.zero, Mathf.Infinity, pieceLayer);

            if (hit.collider != null)
            {
                Piece clickedPiece = hit.collider.gameObject.GetComponent<Piece>();

                if (clickedPiece != null && clickedPiece.isWhite == isWhiteTurn)
                {
                    SelectPiece(hit.collider.gameObject);
                }
            }
            else if (selectedPiece != null)
            {
                Vector2Int targetSquare = new Vector2Int(Mathf.RoundToInt(hit.point.x), Mathf.RoundToInt(hit.point.y));
                TryMove(targetSquare);
            }
        }
    }

    private void SelectPiece(GameObject piece)
    {
        selectedPiece = piece;
    }

    private void DeselectPiece()
    {
        selectedPiece = null;
    }

    private void TryMove(Vector2Int targetSquare)
    {
        Piece piece = selectedPiece.GetComponent<Piece>();

        if (IsValidMove(piece, targetSquare))
        {
            selectedPiece.transform.position = new Vector3(targetSquare.x, targetSquare.y, 0);
            piece.hasMoved = true;
            DeselectPiece();
            if (piece.pieceType == Piece.PieceType.Pawn && (targetSquare.y == 7 || targetSquare.y == 0))
            {
                PromotePawn(piece);
            }

            isWhiteTurn = !isWhiteTurn;
        }
    }
    private void PromotePawn(Piece pawn)
    {
        pawn.pieceType = Piece.PieceType.Queen;
        // Update the pawn's appearance to match the new piece type
    }


    private bool IsValidMove(Piece piece, Vector2Int targetSquare)
    {
        switch (piece.pieceType)
        {
            case Piece.PieceType.Pawn:
                return IsValidMovePawn(piece, targetSquare);
            case Piece.PieceType.Rook:
                return IsValidMoveRook(piece, targetSquare);
            case Piece.PieceType.Knight:
                return IsValidMoveKnight(piece, targetSquare);
            case Piece.PieceType.Bishop:
                return IsValidMoveBishop(piece, targetSquare);
            case Piece.PieceType.Queen:
                return IsValidMoveQueen(piece, targetSquare);
            case Piece.PieceType.King:
                return IsValidMoveKing(piece, targetSquare);
            default:
                Debug.LogError("Invalid piece type: " + piece.pieceType);
                return false;
        }
    }

    private bool IsValidMovePawn(Piece piece, Vector2Int targetSquare)
    {
        int direction = piece.isWhite ? 1 : -1;
        int startRank = piece.isWhite ? 1 : 6;
        Vector2Int moveVector = targetSquare - piece.currentSquare;

        if (moveVector.x == 0)
        {
            if (moveVector.y == direction && !PieceAtSquare(targetSquare))
            {
                return true;
            }
            if (piece.currentSquare.y == startRank && moveVector.y == (2 * direction) && !PieceAtSquare(targetSquare) && !PieceAtSquare(new Vector2Int(piece.currentSquare.x, piece.currentSquare.y + direction)))
            {
                return true;
            }
        }
        else if (Mathf.Abs(moveVector.x) == 1 && moveVector.y == direction)
        {
            Piece targetPiece = GetPieceAtSquare(targetSquare);
            if (targetPiece != null && targetPiece.isWhite != piece.isWhite)
            {
                return true;
            }
        }

        Piece enPassantTarget = GetPieceAtSquare(new Vector2Int(targetSquare.x, piece.currentSquare.y));
        if (enPassantTarget != null && enPassantTarget.pieceType == Piece.PieceType.Pawn && enPassantTarget.isWhite != piece.isWhite && Mathf.Abs(enPassantTarget.currentSquare.y - piece.currentSquare.y) == 1)
        {
            return true;
        }

        if (IsMovePuttingKingInCheck(piece, targetSquare))
        {
            return false;
        }
        return false;
    }


    private bool IsValidMoveRook(Piece piece, Vector2Int targetSquare)
    {
        Vector2Int moveVector = targetSquare - piece.currentSquare;

        if (moveVector.x == 0 || moveVector.y == 0)
        {
            if (!AreSquaresInThePathBlocked(piece.currentSquare, targetSquare))
            {
                if (IsMovePuttingKingInCheck(piece, targetSquare))
                {
                    return false;
                }
                return true;
            }
        }

        return false;
    }

    private bool IsValidMoveKnight(Piece piece, Vector2Int targetSquare)
    {
        Vector2Int moveVector = targetSquare - piece.currentSquare;
        int distance = Mathf.Abs(moveVector.x) + Mathf.Abs(moveVector.y);

        if (distance == 3 && Mathf.Abs(moveVector.x) > 0 && Mathf.Abs(moveVector.y) > 0)
        {
            if (IsMovePuttingKingInCheck(piece, targetSquare))
            {
                return false;
            }
            return true;
        }

        return false;
    }

    private bool IsValidMoveBishop(Piece piece, Vector2Int targetSquare)
    {
        Vector2Int moveVector = targetSquare - piece.currentSquare;

        if (Mathf.Abs(moveVector.x) == Mathf.Abs(moveVector.y))
        {
            if (!AreSquaresInThePathBlocked(piece.currentSquare, targetSquare))
            {
                if (IsMovePuttingKingInCheck(piece, targetSquare))
                {
                    return false;
                }
                return true;
            }
        }

        return false;
    }

    private bool IsValidMoveQueen(Piece piece, Vector2Int targetSquare)
    {
        if (IsValidMoveRook(piece, targetSquare) || IsValidMoveBishop(piece, targetSquare))
        {
            if (IsMovePuttingKingInCheck(piece, targetSquare))
            {
                return false;
            }
            return true;
        }

        return false;
    }

    private bool IsValidMoveKing(Piece piece, Vector2Int targetSquare)
    {
        Vector2Int moveVector = targetSquare - piece.currentSquare;
        int distance = Mathf.Abs(moveVector.x) + Mathf.Abs(moveVector.y);

        if (distance == 1 || (Mathf.Abs(moveVector.x) == 1 && Mathf.Abs(moveVector.y) == 1))
        {
            if (IsMovePuttingKingInCheck(piece, targetSquare))
            {
                return false;
            }
            return true;
        }

        if (!piece.hasMoved)
        {
            Vector2Int rookSquare;
            Piece rook;

            if (moveVector == new Vector2Int(-2, 0))
            {
                rookSquare = new Vector2Int(piece.currentSquare.x - 4, piece.currentSquare.y);
                rook = GetPieceAtSquare(rookSquare);

                if (rook != null && !rook.hasMoved && !AreSquaresInThePathBlocked(piece.currentSquare, rookSquare))
                {
                    if (!IsMovePuttingKingInCheck(piece, piece.currentSquare + new Vector2Int(-1, 0)) && !IsMovePuttingKingInCheck(piece, piece.currentSquare + new Vector2Int(-2, 0)))
                    {
                        return true;
                    }
                }
            }
            else if (moveVector == new Vector2Int(2, 0))
            {
                rookSquare = new Vector2Int(piece.currentSquare.x + 3, piece.currentSquare.y);
                rook = GetPieceAtSquare(rookSquare);

                if (rook != null && !rook.hasMoved && !AreSquaresInThePathBlocked(piece.currentSquare, rookSquare))
                {
                    if (!IsMovePuttingKingInCheck(piece, piece.currentSquare + new Vector2Int(1, 0)) && !IsMovePuttingKingInCheck(piece, piece.currentSquare + new Vector2Int(2, 0)))
                    {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    private bool PieceAtSquare(Vector2Int square)
    {
        return GetPieceAtSquare(square) != null;
    }

    private Piece GetPieceAtSquare(Vector2Int square)
    {
        foreach (Piece piece in board.GetAllPieces())
        {
            if (piece.currentSquare == square) 
            {
                return piece;
            }
        }
        return null;
    }

    private bool AreSquaresInThePathBlocked(Vector2Int startSquare, Vector2Int endSquare)
    {
        Vector2Int moveVector = endSquare - startSquare;
        int steps = Mathf.Max(Mathf.Abs(moveVector.x), Mathf.Abs(moveVector.y));
        Vector2Int direction = new Vector2Int(moveVector.x / steps, moveVector.y / steps);
        Vector2Int currentSquare = startSquare + direction;

        for (int i = 1; i < steps; i++)
        {
            if (PieceAtSquare(currentSquare))
            {
                return true;
            }
            currentSquare += direction;
        }

        return false;
    }

    private bool IsMovePuttingKingInCheck(Piece piece, Vector2Int targetSquare)
    {
        Vector2Int originalPosition = piece.currentSquare;
        Piece targetPiece = GetPieceAtSquare(targetSquare);

        // Simulate the move
        piece.currentSquare = targetSquare;
        if (targetPiece != null)
        {
            board.RemovePiece(targetPiece);
        }

        bool isInCheck = IsKingInCheck(piece.isWhite);

        // Undo the move
        piece.currentSquare = originalPosition;
        if (targetPiece != null)
        {
            board.AddPiece(targetPiece);
        }

        return isInCheck;
    }

    private bool IsKingInCheck(bool isWhite)
    {
        Vector2Int kingPosition = Vector2Int.zero;
        List<Piece> enemyPieces = new List<Piece>();

        // Find the King's position and collect all enemy pieces
        foreach (Piece piece in board.GetAllPieces())
        {
            if (piece.isWhite == isWhite && piece.pieceType == Piece.PieceType.King)
            {
                kingPosition = piece.currentSquare;
            }
            else if (piece.isWhite != isWhite)
            {
                enemyPieces.Add(piece);
            }
        }

        // Check if any enemy piece has a valid move to the King's position
        foreach (Piece enemyPiece in enemyPieces)
        {
            if (IsValidMove(enemyPiece, kingPosition))
            {
                return true;
            }
        }

        return false;
    }


}
