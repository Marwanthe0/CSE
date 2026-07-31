using System.ComponentModel.DataAnnotations;

namespace WebApp1;

public record UpdateProductDTO(
    [Required] [StringLength(50)] string Name,
    [Range(1, 50)] int CategoryId,
    DateOnly ReleaseDate
);
