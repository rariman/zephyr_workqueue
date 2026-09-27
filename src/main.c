#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(workqueue_sample, LOG_LEVEL_INF);

#define LED0_NODE DT_ALIAS(led0)

const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

void work_handler(struct k_work *work)
{
        gpio_pin_toggle_dt(&led);
        LOG_INF("LED toggled");
}

K_WORK_DEFINE(work, work_handler);

void timer_handler(struct k_timer *timer)
{
        k_work_submit(&work);
}

K_TIMER_DEFINE(timer, timer_handler, NULL);

int main(void)
{
        if (!device_is_ready(led.port)) {
                LOG_ERR("LED device not ready");
                return 0;
        }

        int ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);

        if (ret) {
                LOG_ERR("Failed to configure LED");
                return 0;
        }

        k_timer_start(&timer, K_MSEC(CONFIG_TIMER_INTERVAL), K_MSEC(CONFIG_TIMER_INTERVAL));
        return 0;
}
