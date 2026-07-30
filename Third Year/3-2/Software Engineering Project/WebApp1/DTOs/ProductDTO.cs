namespace DTOs;

public record ProductDTO(
int Id,
string Name,
string Category,
DateOnly ReleaseDate
);