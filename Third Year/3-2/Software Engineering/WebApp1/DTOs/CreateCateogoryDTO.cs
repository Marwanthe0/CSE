using System.ComponentModel.DataAnnotations;

namespace WebApp1;

public record CreateCategoryDTO([Required] [StringLength(50)] string Name);
