/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enumeration.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:30:54 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/08 18:31:01 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

// Define enum for traffic lights
typedef enum {
    RED,
    YELLOW,
    GREEN
} TrafficLight;

int main() {
    TrafficLight light = RED;

    // Check the light using if statements
    if (light == RED) {
        printf("Stop!\n");
    } else if (light == YELLOW) {
        printf("Get ready...\n");
    } else if (light == GREEN) {
        printf("Go!\n");
    }

    // You can also do simple arithmetic with enums
    printf("RED has value %d, GREEN has value %d\n", RED, GREEN);

    // Changing the light
    light = GREEN;
    if (light == GREEN) {
        printf("Now you can go!\n");
    }

    return 0;
}
