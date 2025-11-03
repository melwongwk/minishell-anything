/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quick_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 21:17:50 by melwong           #+#    #+#             */
/*   Updated: 2025/07/14 21:34:28 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_swap_int(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	insertion_sort(int *arr, int low, int high)
{
	int	i;
	int	j;
	int	key;

	i = low + 1;
	while (i <= high)
	{
		key = arr[i];
		j = i - 1;
		while (j >= low && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
		i++;
	}
}

static void	median_of_three(int *arr, int low, int high)
{
	int	mid;

	mid = low + (high - low) / 2;
	if (arr[mid] < arr[low])
		ft_swap_int(&arr[mid], &arr[low]);
	if (arr[high] < arr[low])
		ft_swap_int(&arr[high], &arr[low]);
	if (arr[mid] > arr[high])
		ft_swap_int(&arr[mid], &arr[high]);
	ft_swap_int(&arr[mid], &arr[high]);
}

static int	partition(int *arr, int low, int high)
{
	int	pivot;
	int	i;
	int	j;

	median_of_three(arr, low, high);
	pivot = arr[high];
	i = low - 1;
	j = low;
	while (j < high)
	{
		if (arr[j] < pivot)
		{
			i++;
			ft_swap_int(&arr[i], &arr[j]);
		}
		j++;
	}
	ft_swap_int(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void	ft_quick_sort(int *arr, int low, int high)
{
	int	p;

	while (low < high)
	{
		if (high - low <= QSORT_THRESHOLD)
		{
			insertion_sort(arr, low, high);
			break ;
		}
		p = partition(arr, low, high);
		if (p - low < high - p)
		{
			ft_quick_sort(arr, low, p - 1);
			low = p + 1;
		}
		else
		{
			ft_quick_sort(arr, p + 1, high);
			high = p - 1;
		}
	}
}
